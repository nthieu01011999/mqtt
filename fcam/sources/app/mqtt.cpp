#include "app_data.h"
#include "task_list.h"
#include "mqtt.hpp"
#include <ctime>
#include <sstream>
#include <chrono>
#include <nlohmann/json.hpp>



mqtt::mqtt(mqttTopicCfg_t *mqtt_parameter, mtce_netMQTT_t *mqtt_config) : mosquittopp(mqtt_config->clientID, true) {
	APP_DBG("[mqtt][CONSTRUCTOR]\n");
	mosqpp::lib_init();
	
	/* init private data */
	m_mid		= 0;	// messages ID
	m_connected = false;
	lenLastMsg	= 0;
	lastMsgPtr	= NULL;

	/* save some data */
	memset(&m_cfg, 0, sizeof(m_cfg));
	memset(&m_topics, 0, sizeof(m_topics));
	memcpy(&m_cfg, mqtt_config, sizeof(m_cfg));
	memcpy(&m_topics, mqtt_parameter, sizeof(m_topics));

	/* setup conection */
	if (m_cfg.username && m_cfg.password) {
		username_pw_set(m_cfg.username, m_cfg.password);
	}
}

bool mqtt::connectBroker() {
    // int connectResult = connect(m_cfg.host, m_cfg.port, m_cfg.keepAlive);
    int connectResult = connect_async(m_cfg.host, m_cfg.port, m_cfg.keepAlive);
    if (connectResult == MOSQ_ERR_SUCCESS) {
        APP_DBG("[MQTT] Connected to broker\n");
		// Start the event loop
		int loopResult = loop_start();
        if (loopResult == MOSQ_ERR_SUCCESS) {
            APP_DBG("[MQTT] Event loop started successfully\n");
            return true;
        } else {
            APP_DBG("[MQTT] Failed to start event loop: %s\n", mosquitto_strerror(loopResult));
            return false;
        }
    } else {
        APP_DBG("[MQTT] Failed to connect to broker: %s\n", mosquitto_strerror(connectResult));
        return false;
    }
    
}

void mqtt::on_log(int level, const char *log_str) {
	if (!isConnected()) {
		APP_DBG("[MQTT][onLog] -> %s\n", log_str);
	}
	return;
}

void mqtt::setConnected(bool state) {
	m_connected = state;
}

bool mqtt::isConnected() {
	return m_connected;
}

int *mqtt::genMsgId() {
	return &(++m_mid);
}

bool mqtt::subcribePerform(const std::string &topic) {
    if (isConnected()) {
        int result = subscribe(&(++m_mid), topic.c_str());
        return result == MOSQ_ERR_SUCCESS;
    }
    return false;
}

std::string mqtt::getCurrentTimestamp() { // Definition
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << now_c;
    return oss.str();
}


void mqtt::on_connect(int rc) {
    if (rc == 0) {
        APP_DBG("[MQTT_CONTROL] on_connect OK\n");
        setConnected(true);

        // Subscribe to necessary topics
        std::vector<std::string> topics = {m_topics.topicRequest, m_topics.topicResponse, m_topics.topicStatus};
        for (const auto& topic : topics) {
            APP_DBG("[mqtt] Attempt to subscribe topic [%s]\n", topic.c_str());
            if (!subcribePerform(topic)) {
                APP_DBG("[mqtt] Failed to subscribe to topic: %s\n", topic.c_str());
            } else {
                APP_DBG("[mqtt] Subscribed to topic: %s\n", topic.c_str());
            }
        }

        // Publish a message to the request topic
        std::string message = "{\"msg\": \"Hello from Client @ APP!\", \"timestamp\": \"" + getCurrentTimestamp() + "\"}";
        // std::string message = "{\"msg\": \"Hello from Client @ APP, I AM " + mqttConfig->clientID + "!\", \"timestamp\": \"" + getCurrentTimestamp() + "\"}";
        if (publishMessage(m_topics.topicRequest, message)) {
            // APP_DBG("[mqtt] Successfully published message to topic [%s]\n", m_topics.topicRequest);
        } else {
            // APP_DBG("[mqtt] Failed to publish message to topic [%s]\n", m_topics.topicRequest);
        }
    } else {
        APP_DBG("[MQTT_CONTROL] on_connect ERROR: %d\n", rc);
        setConnected(false);
    }
}


bool mqtt::publishMessage(const std::string &topic, const std::string &message) {
  if (isConnected()) {
    // Check if message is a reply (optional: avoid republishing replies)
    if (message.find("Reply to:") == std::string::npos) {
      // Format message to include client ID and timestamp
      std::string formattedMessage = message + ", \"clientID\": \"" + 
                                     mqttConfig.clientID + "\", \"timestamp\": \"" +
                                     getCurrentTimestamp() + "\"";

      // Publish the formatted message
      int result = publish(NULL, topic.c_str(), formattedMessage.size(),
                            formattedMessage.c_str(), m_cfg.QOS, false);

      if (result != MOSQ_ERR_SUCCESS) {
        APP_DBG("[mqtt] Failed to publish message to topic: %s, error: %s\n",
                topic.c_str(), mosquitto_strerror(result));
        return false;
      }
      return true;
    } else {
      // Optional: log skipped publishing of replies (for debugging)
      // APP_DBG("[mqtt] Skipped publishing reply to avoid loop: %s\n", message.c_str());
    }
  }
  return false;
}





void mqtt::on_publish(int mid) {
	// APP_DBG("[mqtt][on_publish] mid: %d\n", mid);
}

void mqtt::on_subscribe(int mid, int qos_count, const int *granted_qos) {
	(void)granted_qos;
	// APP_DBG("[mqtt][on_subscribe] mid:%d\tqos_count:%d\n", mid, qos_count);
}

void mqtt::on_message(const struct mosquitto_message *message) {
  if (message->payloadlen > 0) {
    // Convert the payload to a string
    std::string payload(static_cast<char*>(message->payload), message->payloadlen);

    // Log the received message for debugging
    
    // std::string extractedClientId = getClientIdFromPayload(payload);
    std::string extractedClientId = extractClientID(payload);
    // Access client ID from member variable (assuming dependency injection)
    // std::cout << "Client ID from member variable: " << m_mqttConfig->clientID << std::endl;
    std::cout << "[2] Client ID from member variable: " << mqttConfig.clientID << std::endl;
    std::cout << "[MAIN] Client ID from member variable: " << extractedClientId << std::endl;
    std::string clientId = mqttConfig.clientID;

    // Check if message contains our client ID (for filtering)
    if (extractedClientId == mqttConfig.clientID) {
        // Skip processing if it's our own message
        // APP_DBG("[mqtt][on_message] Ignoring self-published message.\n");
        return;
    }
    //do not delete it     APP_DBG("[mqtt][on_message] Received message on topic: %s, payload: %s\n", message->topic, payload.c_str());
    // APP_DBG("[mqtt][on_message] Received message on topic: %s, payload: %s\n", message->topic, payload.c_str());
    task_post_common_msg(GW_TASK_WEBRTC_ID, GW_CLOUD_HANDLE_INCOME_MESSAGE, (uint8_t*)payload.data(), payload.size());
    } else {
        APP_DBG("[mqtt][on_message] Received empty message on topic: %s\n", message->topic);
    }
}

std::string mqtt::getClientIdFromPayload(const std::string& payload) {
  // Assuming the client ID is within a JSON object with key "clientID"
  std::string key = "\"clientID\":";
  size_t pos = payload.find(key);
  if (pos != std::string::npos) {
    // Extract the value after the key and colon
    size_t start = pos + key.length() + 1; // Skip key, colon, and quote
    size_t end = payload.find('"', start);
    if (end != std::string::npos) {
      std::string extractedClientId = payload.substr(start, end - start);
      // Print the extracted client ID
      std::cout << "Extracted client ID: " << extractedClientId << std::endl;
      return extractedClientId;
    }
  }

  // Client ID not found, print a message and return an empty string
  std::cout << "Client ID not found in payload" << std::endl;
  return "";
}


// Separate function to handle incoming message logic
void mqtt::handleIncomingMessage(const char* topic, const std::string& payload) {
  // Get the current timestamp
  std::string timestamp = getCurrentTimestamp();

  // Check if the message already contains a reply to avoid loops
  if (payload.find("Reply to:") == std::string::npos) {
    std::string replyMessage = "{\"msg\": \"Reply to: " + payload + "\", \"timestamp\": \"" + timestamp + "\"}";

    // Publish the reply message based on topic (assuming dependency injection)
    if (strcmp(topic, m_topicConfig->topicRequest) == 0) { // Example: reply on request topic
      APP_DBG("[mqtt][on_message] Publishing reply to 'example/response': %s\n", replyMessage.c_str());
      publishMessage(m_topicConfig->topicResponse, replyMessage);
    } else {
      APP_DBG("[mqtt][on_message] Received message on an unknown topic: %s\n", topic);
    }
  } else {
    APP_DBG("[mqtt][on_message] Skipping message to avoid loop: %s\n", payload.c_str());
  }
}


void mqtt::on_disconnect(int rc) {
    APP_DBG("[MQTT] Disconnected from broker with return code: %d\n", rc);
    if (rc != 0) {
        APP_DBG("[MQTT] Unexpected disconnection, reason: %s\n", mosquitto_strerror(rc));
    }
    setConnected(false);
}

void mqtt::interactiveChat() {
    std::string userInput;
    while (true) {
        std::cout << "Type a message to send: \n";
        std::getline(std::cin, userInput);
        if (userInput.empty()) continue;

        if (!publishMessage("example/request", userInput)) {
            std::cout << "Failed to send message. Try again." << std::endl;
        } else {
            std::cout << "Message sent: " << userInput << std::endl;
        }
    }
}

void mqtt::startClient() {
    // Wait until the client is connected
    while (!isConnected()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    interactiveChat();
}

 

std::string mqtt::extractClientID(const std::string& payload) {
    std::string clientIdKey = "\"clientID\": \"";
    size_t start = payload.find(clientIdKey);
    if (start == std::string::npos) {
        return "Client ID not found";
    }

    start += clientIdKey.length();  // Move start to the beginning of the client ID value
    size_t end = payload.find("\"", start);  // Find the end of the client ID value
    if (end == std::string::npos) {
        return "Invalid payload format";
    }

    return payload.substr(start, end - start);
}