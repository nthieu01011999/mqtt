#!/bin/bash
# Define MQTT broker details
BROKER="mqtt://127.0.0.1:1883"
TOPIC="test/topic1"

# Path to MQTTx executable
MQTTX_PATH="/usr/local/bin/mqttx" # Replace with the actual path to your MQTTx executable

# Initialize MQTTx configuration with Text mode (do this once, then comment out)
# "$MQTTX_PATH" init --mode text

# Create MQTTx Client 1 connection
"$MQTTX_PATH" conn --broker $BROKER --client-id Client1 &
CLIENT1_PID=$!  # Capture PID to manage process

# Create MQTTx Client 2 connection
"$MQTTX_PATH" conn --broker $BROKER --client-id Client2 &
CLIENT2_PID=$!  # Capture PID to manage process

# Wait a moment to ensure connections are established
sleep 2

# Subscribe Client 1 to the topic
"$MQTTX_PATH" sub --topic $TOPIC --client-id Client1 --qos 0 &> client1_sub.log &

# Subscribe Client 2 to the topic
"$MQTTX_PATH" sub --topic $TOPIC --client-id Client2 --qos 0 &> client2_sub.log &

# Wait a moment to ensure subscriptions are established
sleep 2

# Test message publishing from Client 1
"$MQTTX_PATH" pub --topic $TOPIC --message "Hello from Client1" --client-id Client1 --qos 0

# Test message publishing from Client 2
"$MQTTX_PATH" pub --topic $TOPIC --message "Hello from Client2" --client-id Client2 --qos 0

# Optional: Keep script running or manage clients
# wait $CLIENT1_PID $CLIENT2_PID  # Uncomment to keep script running until clients are manually closed

