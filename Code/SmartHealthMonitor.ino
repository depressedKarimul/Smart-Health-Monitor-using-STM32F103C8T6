#include <Wire.h>
#include <LiquidCrystal.h>
#include "MAX30100_PulseOximeter.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define REPORTING_PERIOD_MS 1000

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(PA0, PA1, PA2, PA3, PA4, PA5);

// MAX30100
PulseOximeter pox;
unsigned long lastPoxRead = 0;

// DS18B20
#define ONE_WIRE_BUS PB0
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float temperature = 0.0;
unsigned long lastTempRead = 0;

// General
unsigned long lastDisplaySwitch = 0;
int mode = 0; // 0: idle, 1: MAX30100, 2: Temp

void onBeatDetected() {
  lcd.setCursor(0, 1);
  lcd.print("Beat Detected  ");
}

void setup() {
  Wire.begin();
  lcd.begin(16, 2);
  lcd.print("Initializing...");

  // Try to start MAX30100 (retry if needed)
  bool success = false;
  for (int i = 0; i < 5; i++) {
    if (pox.begin()) {
      success = true;
      break;
    }
    delay(500);
  }

  if (!success) {
    lcd.setCursor(0, 1);
    lcd.print("MAX30100 Fail");
    while (1); // Halt
  }

  pox.setIRLedCurrent(MAX30100_LED_CURR_11MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);

  // Start DS18B20
  sensors.begin();

  lcd.clear();
  lcd.print("Place finger or");
  lcd.setCursor(0, 1);
  lcd.print("touch sensor...");
}

void loop() {
  unsigned long now = millis();

  // --- MAX30100 ---
  pox.update();

  if (now - lastPoxRead > REPORTING_PERIOD_MS) {
    float hr = pox.getHeartRate();
    float spo2 = pox.getSpO2();
    lastPoxRead = now;

    if (hr > 30 && hr < 200 && spo2 > 70 && spo2 < 100) {
      mode = 1;
      lastDisplaySwitch = now;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("HR: ");
      lcd.print(hr, 0);
      lcd.print(" bpm");

      lcd.setCursor(0, 1);
      lcd.print("SpO2: ");
      lcd.print(spo2, 0);
      lcd.print(" %  ");
    }
  }

  // --- DS18B20 ---
  if (now - lastTempRead > 1500) {
    sensors.requestTemperatures();
    float temp = sensors.getTempCByIndex(0);
    lastTempRead = now;

    if (temp != DEVICE_DISCONNECTED_C && temp > 20 && temp < 50) {
      temperature = temp;
      mode = 2;
      lastDisplaySwitch = now;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temperature:");

      lcd.setCursor(0, 1);
      lcd.print(temperature, 1);
      lcd.print((char)223); // degree symbol
      lcd.print("C       ");
    }
  }

  // --- Return to Idle After 5s ---
  if ((now - lastDisplaySwitch > 5000) && mode != 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Place finger or");
    lcd.setCursor(0, 1);
    lcd.print("touch sensor...");
    mode = 0;
  }
}