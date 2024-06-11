#include "app_data.h"
#include "task_list.h"
#include "mqtt.hpp"

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

bool mqtt::isConnected(void) {
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
        std::string message = "{\"msg\": \"Hello from Client @ APP!\"}";
        if (publishMessage(m_topics.topicRequest, message)) {
            APP_DBG("[mqtt] Successfully published message to topic [%s]\n", m_topics.topicRequest);
        } else {
            APP_DBG("[mqtt] Failed to publish message to topic [%s]\n", m_topics.topicRequest);
        }
    } else {
        APP_DBG("[MQTT_CONTROL] on_connect ERROR: %d\n", rc);
        setConnected(false);
    }
}


bool mqtt::publishMessage(const std::string &topic, const std::string &message) {
    if (isConnected()) {
        return (publish(NULL, topic.c_str(), message.size(), message.c_str(), m_cfg.QOS, false) == MOSQ_ERR_SUCCESS);
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
    APP_DBG("[mqtt][on_message] topic: %s, payload: %s\n", message->topic, static_cast<char*>(message->payload));

    if (message->payloadlen > 0) {
        std::string payload(static_cast<char*>(message->payload), message->payloadlen);
        
        // Process the message based on the topic
        if (strcmp(message->topic, m_topics.topicRequest) == 0) {
            APP_DBG("[mqtt][on_message] Processing message for topicRequest: %s\n", payload.c_str());
            // Process the payload
        } else if (strcmp(message->topic, m_topics.topicResponse) == 0) {
            APP_DBG("[mqtt][on_message] Processing message for topicResponse: %s\n", payload.c_str());
            // Process the payload
        } else if (strcmp(message->topic, m_topics.topicStatus) == 0) {
            APP_DBG("[mqtt][on_message] Processing message for topicStatus: %s\n", payload.c_str());
            // Process the payload
        } else {
            APP_DBG("[mqtt][on_message] Unknown topic: %s\n", message->topic);
        }
    }
}

void mqtt::on_disconnect(int rc) {
    APP_DBG("[MQTT] Disconnected from broker with return code: %d\n", rc);
    if (rc != 0) {
        APP_DBG("[MQTT] Unexpected disconnection, reason: %s\n", mosquitto_strerror(rc));
    }
    setConnected(false);
}
