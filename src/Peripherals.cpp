#include <Arduino.h>
#include <DHT.h>

#include "Peripherals.h"
#include "State.h"
#include "config.h"

DHT dht(DHT_PIN, DHT_TYPE);

bool pluginFlag = true;
bool plugoutFlag = true;

float mapFloat(long value, long inMin, long inMax,
               float outMin, float outMax) {
  return (value - inMin) * (outMax - outMin) /
         float(inMax - inMin) + outMin;
}

void sample_sensor(void) {
  int rawCurrent = analogRead(CURRENT_PIN);
  int rawVoltage = analogRead(VOLTAGE_PIN);

  voltage = mapFloat(rawVoltage, 0, 4095, 0.0f, 250.0f);

  if (bayStatus == "CHARGING") 
  {
    current = mapFloat(rawCurrent, 0, 4095, 0, 32);
  } 
  else
  {
    current = 0.;
  }

  power = voltage * current;

  float t = dht.readTemperature();
  if (!isnan(t)) {
    temperature = t;
  }
}

float recentAvgCurrent(void) {
  float sum = 0.0f;
  for (int i = 0; i < 5; i++) {
    sum += current;
  }
  return sum / 5.0f;
}

void plug_status(void) {
  bool pluginReading = digitalRead(BTN_PLUGIN);

  if (pluginReading == LOW && pluginFlag) {
    pluginFlag = false;

    if (bayStatus == "FREE") {
      sessionStartMs = millis();
      bayStatus = "CHARGING";
      Serial.println("Plug-in detected: charging started");
      update_led_Status();
    }
  }

  if (pluginReading == HIGH) {
    pluginFlag = true;
  }

  bool plugoutReading = digitalRead(BTN_PLUGOUT);

  if (plugoutReading == LOW && plugoutFlag) {
    plugoutFlag = false;

    if (bayStatus == "CHARGING") {
      bayStatus = "FREE";
      Serial.println("Plug-out detected: bay is free");
      update_led_Status();
    }
  }

  if (plugoutReading == HIGH) {
    plugoutFlag = true;
  }
}

void update_led_Status(void) {
  digitalWrite(LED_GREEN, (bayStatus == "CHARGING") ? HIGH : LOW);
  digitalWrite(LED_YELLOW, (bayStatus == "FREE") ? HIGH : LOW);
  digitalWrite(LED_RED, LOW);
}