#include <Arduino.h>
#include <WiFi.h>

#include "State.h"
#include "config.h"
#include "Peripherals.h"
#include "Network.h"
#include "telemetry.h"
#include "model.h"
#include "edge_ai.h"
#include "optimization.h"

unsigned long now = 0;
unsigned long last_print = 0;

void setup()  
 {

  mqtt.loop();
  Serial.begin(115200);

  dht.begin();

  configTime(0, 0, "pool.ntp.org", "time.nist.gov");

  pinMode(BTN_PLUGIN, INPUT_PULLUP);
  pinMode(BTN_PLUGOUT, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  update_led_Status();
  connectWiFi();

  mqtt.setServer(MQTT_SERVER, MQTT_PORT);
  connectMQTT();
}

void loop() {
  now = millis();

  if (now - last_print > 5000) {
    last_print = now;

    sample_sensor();
    runEdgeAIInference();
    runOptimization();
    publishTelemetry();
  }

  plug_status();
  update_led_Status();
}