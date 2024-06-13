#ifndef __MQTT__H__
#define __MQTT__H__

#include <stdint.h>
#include <string.h>
#include <atomic>
#include <mosquittopp.h>

#include "ak.h"

#include "app.h"
#include "app_dbg.h"
#include "task_webrtc.h"

extern mtce_netMQTT_t mqttConfig;

class mqtt : public mosqpp::mosquittopp {
public:
	mqtt(mqttTopicCfg_t *mqtt_parameter, mtce_netMQTT_t *mqtt_config);
	~mqtt() {
		loop_stop(true);	// Force stop thread (true)
		if (lastMsgPtr != NULL) {
			free(lastMsgPtr);
		}
		// disconnect();
		mosqpp::lib_cleanup();
		APP_DBG("~mqtt() called\n");
	}
	void displayChatMessage(const std::string& payload);
	void interactiveChat();
	void postIncomingMessageToTask(const std::string &payload);
	void startClient();
    bool connectBroker();
	bool subcribePerform(const std::string &topic);
	bool publishMessage(const std::string &topic, const std::string &message);
	
	// getter and setter
	void setConnected(bool state);
	bool isConnected();
	int *genMsgId();

	// Callback functions
	void on_connect(int rc);
	void on_disconnect(int rc);
	void on_publish(int mid);
	void on_subscribe(int mid, int qos_count, const int *granted_qos);
	void on_message(const struct mosquitto_message *message);
	void on_log(int level, const char *log_str);

 

private:
	std::string extractClientID(const std::string& payload);
	std::string getCurrentTimestamp();
	// store topic: default it will sub 1 topic when MQTT is connected
	mtce_netMQTT_t m_cfg;
	mqttTopicCfg_t m_topics;
	int m_mid;
	std::atomic<bool> m_connected;
	int lenLastMsg;
	uint8_t *lastMsgPtr;
	
	const mtce_netMQTT_t* m_mqttConfig;
	const mqttTopicCfg_t* m_topicConfig;

	// Function to handle incoming message logic
	std::string getClientIdFromPayload(const std::string& payload);
};

#endif	  //__MQTT__H__