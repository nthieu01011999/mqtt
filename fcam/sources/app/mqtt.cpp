#include "app_data.h"
#include "task_list.h"
#include "mqtt.hpp"
#include <ctime>
#include <sstream>
#include <chrono>
 

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
        // Check if message is a reply and avoid republishing it
        if (message.find("Reply to:") == std::string::npos) {
            std::string timestampedMessage = message + ", \"timestamp\": \"" + getCurrentTimestamp() + "\"";
            int result = publish(NULL, topic.c_str(), timestampedMessage.size(), timestampedMessage.c_str(), m_cfg.QOS, false);
            if (result != MOSQ_ERR_SUCCESS) {
                APP_DBG("[mqtt] Failed to publish message to topic: %s, error: %s\n", topic.c_str(), mosquitto_strerror(result));
                return false;
            }
            return true;
        } else {
            // APP_DBG("[mqtt] Skipped publishing reply to avoid loop: %s\n", message.c_str());
        }
    }
    return false;
}




void mqtt::on_publish(int mid) {
	APP_DBG("[mqtt][on_publish] mid: %d\n", mid);
}

void mqtt::on_subscribe(int mid, int qos_count, const int *granted_qos) {
	(void)granted_qos;
	APP_DBG("[mqtt][on_subscribe] mid:%d\tqos_count:%d\n", mid, qos_count);
}

void mqtt::on_message(const struct mosquitto_message *message) {
    if (message->payloadlen > 0) {
        // Convert the payload to a string
        std::string payload(static_cast<char*>(message->payload), message->payloadlen);

        // Log the received message for debugging
        APP_DBG("[mqtt][on_message] Received message on topic: %s, payload: %s\n", message->topic, payload.c_str());

        // Get the current timestamp
        std::string timestamp = getCurrentTimestamp();

        // Check if the message already contains a reply to avoid loops
        if (payload.find("Reply to:") == std::string::npos) {
            std::string replyMessage = "{\"msg\": \"Reply to: " + payload + "\", \"timestamp\": \"" + timestamp + "\"}";

            // Publish the reply message to the appropriate topic
            if (strcmp(message->topic, "example/request") == 0) {
                APP_DBG("[mqtt][on_message] Publishing reply to 'example/response': %s\n", replyMessage.c_str());
                publishMessage("example/response", replyMessage);
            } else if (strcmp(message->topic, "example/response") == 0) {
                APP_DBG("[mqtt][on_message] Publishing reply to 'example/request': %s\n", replyMessage.c_str());
                publishMessage("example/request", replyMessage);
            } else {
                APP_DBG("[mqtt][on_message] Received message on an unknown topic: %s\n", message->topic);
            }
        } else {
            APP_DBG("[mqtt][on_message] Skipping message to avoid loop: %s\n", payload.c_str());
        }
    } else {
        APP_DBG("[mqtt][on_message] Received empty message on topic: %s\n", message->topic);
    }
}




void mqtt::handleIncomingMessage(const std::string &topic, const std::string &message) {
    // Determine the correct topic for replies
    std::string replyTopic = (topic == m_topics.topicRequest) ? m_topics.topicResponse : m_topics.topicRequest;

    // Create reply message
    std::string reply = "{\"msg\": \"Reply to: " + message + "\"}";
    APP_DBG("Publishing reply message to %s: %s\n", replyTopic.c_str(), reply.c_str());

    // Publish reply
    publishMessage(replyTopic, reply);
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
