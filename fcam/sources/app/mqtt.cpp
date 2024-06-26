#include <mutex>
#include "app_data.h"
#include "task_list.h"
#include "mqtt.hpp"
#include <ctime>
#include <sstream>
#include <chrono>
#include <nlohmann/json.hpp>
#include "app.h"
#include "app_dbg.h"
#include <termios.h>
#include <unistd.h>
 #include <unordered_map>
#include <string>

std::mutex mqtt::colorMutex;  // Initialize the static mutex
std::unordered_map<std::string, std::string> mqtt::userColors;

// ANSI color codes
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";

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

        // Construct JSON message
        nlohmann::json messageJson;
        messageJson["msg"] = "Hello from Client @ APP!";
        messageJson["timestamp"] = getCurrentTimestamp();
        
        std::string message = messageJson.dump(); // Serialize JSON to string

        // Publish a message to the request topic

        // if (publishMessage(m_topics.topicRequest, message)) {
        //     APP_DBG("[mqtt] Successfully published message to topic [%s]\n", m_topics.topicRequest);
        // } else {
        //     APP_DBG("[mqtt] Failed to publish message to topic [%s]\n", m_topics.topicRequest);
        // }
    }
    else {
        APP_DBG("[MQTT_CONTROL] on_connect ERROR: %d\n", rc);
        setConnected(false);
    
    }
}



bool mqtt::publishMessage(const std::string &topic, const std::string &message) {
  if (isConnected()) {
    if (message.find("Reply to:") == std::string::npos) {
      json msgJson;

      try {
        msgJson = json::parse(message);  // Try parsing the message as JSON
        msgJson["clientID"] = mqttConfig.clientID;
        msgJson["timestamp"] = getCurrentTimestamp();
      } catch (json::parse_error&) {
        // If parsing fails, treat it as plain text and add as content
        msgJson["content"] = message;
        msgJson["clientID"] = mqttConfig.clientID;
        msgJson["timestamp"] = getCurrentTimestamp();
      }

      std::string formattedMessage = msgJson.dump();

      // Print the formatted message
    //   APP_DBG("Formatted message to publish: %s\n", formattedMessage.c_str());
      int result = publish(NULL, topic.c_str(), formattedMessage.size(),
                           formattedMessage.c_str(), m_cfg.QOS, false);

      if (result != MOSQ_ERR_SUCCESS) {
        APP_DBG("[mqtt] Failed to publish message to topic: %s, error: %s\n",
                topic.c_str(), mosquitto_strerror(result));
        return false;
      }
      return true;
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
#include "mqtt.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void mqtt::on_message(const struct mosquitto_message *message) {
    try {
        if (message->payloadlen > 0) {
            std::string payload(static_cast<char*>(message->payload), message->payloadlen);
            try {
                json receivedMsg = json::parse(payload);
                std::string extractedClientId = receivedMsg.value("clientID", "Client ID not found");
                if (extractedClientId != mqttConfig.clientID) { // Ensuring it's not a message from this client
                    task_post_common_msg(GW_TASK_WEBRTC_ID, GW_CLOUD_HANDLE_INCOME_MESSAGE, (uint8_t*)payload.data(), payload.size());
                }
            } catch (json::parse_error& e) {
                APP_ERR("[ERROR] Failed to parse JSON message: %s\n", e.what());
            } catch (std::exception& e) {
                APP_ERR("[ERROR] Exception occurred during message handling: %s\n", e.what());
            }
        } else {
            APP_DBG("[mqtt][on_message] Received empty message on topic: %s\n", message->topic);
        }
    } catch (std::exception& e) {
        APP_ERR("[ERROR] Exception occurred in on_message: %s\n", e.what());
    } catch (...) {
        APP_ERR("[ERROR] Unknown error occurred in on_message\n");
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
            APP_DBG("Extracted client ID: %s\n", extractedClientId.c_str());
            return extractedClientId;
        }
    }

    // Client ID not found, print a message and return an empty string
    APP_DBG("Client ID not found in payload\n");
    return "";
}

void mqtt::displayChatMessage(const std::string& payload) {
    try {
        // Parse the JSON payload
        json receivedMsg = json::parse(payload);

        // Extract fields from the payload
        std::string clientID = receivedMsg.value("clientID", "Unknown");
        std::string content = receivedMsg.value("content", "No content");
        std::string timestamp = receivedMsg.value("timestamp", "No timestamp");

        // Display in chat box format
        APP_DBG("\n");
        APP_DBG("User: %s\n", clientID.c_str());
        APP_DBG("Content: %s\n", content.c_str());
        APP_DBG("Timestamp: %s\n", timestamp.c_str());
        APP_DBG("\n");

    } catch (json::parse_error& e) {
        APP_ERR("[ERROR] Failed to parse JSON message: %s\n", e.what());
    } catch (json::type_error& e) {
        APP_ERR("[ERROR] Type error in JSON message: %s\n", e.what());
    } catch (std::exception& e) {
        APP_ERR("[ERROR] Exception while handling message: %s\n", e.what());
    }
}


void mqtt::on_disconnect(int rc) {
    APP_DBG("[MQTT] Disconnected from broker with return code: %d\n", rc);
    if (rc != 0) {
        APP_DBG("[MQTT] Unexpected disconnection, reason: %s\n", mosquitto_strerror(rc));
    }
    setConnected(false);
}

 
 

void mqtt::disableEcho() {
    termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void mqtt::enableEcho() {
    termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void mqtt::interactiveChat() {
    std::string userInput, userID = m_cfg.clientID; // Assuming clientID is defined in your MQTT config
    while (true) {

        disableEcho();  // Disable echo
        std::getline(std::cin, userInput);  // Capture user input silently
        enableEcho();   // Re-enable echo

        std::string timestamp = getCurrentTimestamp();

        // Print message
        printMessage(userID, userInput, timestamp);

        // Assume publishMessage handles sending to MQTT broker
        if (!publishMessage("example/request", userInput)) {
            std::cout << RED << "Failed to send message. Try again." << RESET << std::endl;
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



// Map to hold user-specific colors
std::unordered_map<std::string, std::string> userColors;



// Function to assign a color to a user
std::string mqtt::getColorForUser(const std::string& userID) {
    std::lock_guard<std::mutex> lock(colorMutex);  // Lock the mutex during this operation
    if (userColors.find(userID) != userColors.end()) {
        return userColors[userID];
    } else {
        // Assign a new color randomly
        static const std::vector<std::string> colors = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
        std::string newColor = colors[rand() % colors.size()];
        userColors[userID] = newColor;
        return newColor;
    }
}



void mqtt::printMessage(const std::string& userID, const std::string& content, const std::string& timestamp) {
    std::string color = getColorForUser(userID);
    std::cout << color << "User: " << userID << RESET << std::endl
              << color << "Content: " << content << RESET << std::endl
              << color << "Timestamp: " << timestamp << RESET << std::endl << std::endl;
}