/*
 * ============================================================================
 *  Real-time Monitoring System for Aquaculture using IoT
 * ============================================================================
 *
 *  Description : Arduino-based water quality monitoring system for aquaculture.
 *                Reads temperature, pH, turbidity, conductivity, and water
 *                level sensors and streams data to the Blynk IoT dashboard
 *                for real-time visualization and alerts.
 *
 *  Board       : Arduino Uno / Mega
 *  Libraries   : Blynk, SimpleTimer, SoftwareSerial
 *
 *  Pin Mapping :
 *    A0  -> Turbidity sensor (analog)
 *    A1  -> LM35 Temperature sensor (analog)
 *    A4  -> pH sensor module TX (SoftwareSerial RX)
 *    A5  -> pH sensor module RX (SoftwareSerial TX)
 *    D2  -> Debug serial RX (SoftwareSerial)
 *    D3  -> Debug serial TX (SoftwareSerial)
 *    D6  -> Relay 1 output
 *    D7  -> Relay 2 output
 *    D8  -> Conductivity sensor (digital)
 *    D13 -> Water level sensor (digital)
 *
 *  Blynk Virtual Pins :
 *    V0  -> Relay 1 control (from app)
 *    V1  -> Relay 2 control (from app)
 *    V2  -> Temperature (°C)
 *    V6  -> Turbidity (voltage)
 *    V7  -> Water level status ("Tank Full" / "Tank Empty")
 *    V8  -> Conductivity status ("Conduc High" / "Conduc LOW")
 *    V9  -> pH value
 *
 *  Author      : raghu-007
 *  License     : MIT
 * ============================================================================
 */

#include <Blynk.h>
#include <SoftwareSerial.h>
#include <BlynkSimpleStream.h>
#include <SimpleTimer.h>

// ──────────────────────────────────────────────
//  Configuration
// ──────────────────────────────────────────────

// ⚠️  Replace with YOUR Blynk auth token (from the Blynk app).
//     Never commit real tokens to version control.
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";

// ──────────────────────────────────────────────
//  Pin Definitions
// ──────────────────────────────────────────────

#define TURBIDITY_PIN   A0    // Turbidity sensor (analog)
#define TEMP_PIN        A1    // LM35 temperature sensor (analog)
#define COND_PIN        8     // Conductivity sensor (digital)
#define WATER_LEVEL_PIN 13    // Water level sensor (digital)
#define RELAY_1_PIN     6     // Relay 1
#define RELAY_2_PIN     7     // Relay 2

// ──────────────────────────────────────────────
//  Thresholds
// ──────────────────────────────────────────────

#define TEMP_HIGH_THRESHOLD 30.0  // °C — trigger alert above this

// ──────────────────────────────────────────────
//  Globals
// ──────────────────────────────────────────────

SoftwareSerial DebugSerial(2, 3);     // Debug output
SoftwareSerial phSerial(A4, A5);      // pH sensor module

#define BLYNK_PRINT DebugSerial

SimpleTimer timer;

int   sensorValue;
float voltage;
int   waterVal;
int   condVal     = HIGH;
float tempCelsius;

char  ph_value[8];
int   count  = 0;
int   count1 = 0;

// ──────────────────────────────────────────────
//  Blynk Virtual Pin Handlers
// ──────────────────────────────────────────────

// Relay 1 control from the Blynk app
BLYNK_WRITE(V0) {
  int pinState = param.asInt();
  digitalWrite(RELAY_1_PIN, pinState);
}

// Relay 2 control from the Blynk app
BLYNK_WRITE(V1) {
  int pinState = param.asInt();
  digitalWrite(RELAY_2_PIN, pinState);
}

// ──────────────────────────────────────────────
//  Setup
// ──────────────────────────────────────────────

void setup() {
  DebugSerial.begin(9600);
  Serial.begin(9600);
  phSerial.begin(9600);
  Blynk.begin(auth, Serial);

  // Sensor pins
  pinMode(TURBIDITY_PIN,   INPUT);
  pinMode(WATER_LEVEL_PIN, INPUT);
  pinMode(TEMP_PIN,        INPUT);
  pinMode(COND_PIN,        INPUT);
  digitalWrite(COND_PIN, HIGH);

  // Relay pins
  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);
}

// ──────────────────────────────────────────────
//  Main Loop
// ──────────────────────────────────────────────

void loop() {
  Blynk.run();
  timer.run();

  // ── Temperature (LM35) ──
  int   tempRaw = analogRead(TEMP_PIN);
  float mv      = (tempRaw / 1024.0) * 5000;
  tempCelsius   = mv / 10;
  Blynk.virtualWrite(V2, tempCelsius);

  if (tempCelsius > TEMP_HIGH_THRESHOLD) {
    Blynk.notify("Temperature is too high!");
  }

  // ── Turbidity ──
  sensorValue = analogRead(TURBIDITY_PIN);
  voltage     = sensorValue * (5.0 / 1024.0);
  Blynk.virtualWrite(V6, voltage);

  // ── Water Level ──
  waterVal = digitalRead(WATER_LEVEL_PIN);
  if (waterVal == 1) {
    Blynk.virtualWrite(V7, "Tank Full");
  } else {
    Blynk.virtualWrite(V7, "Tank Empty");
    Blynk.notify("Water is getting low, please take care!");
  }

  // ── Conductivity ──
  condVal = digitalRead(COND_PIN);
  if (condVal == 0) {
    Blynk.virtualWrite(V8, "Conduc High");
  } else {
    Blynk.virtualWrite(V8, "Conduc LOW");
  }

  // ── pH Sensor ──
  delay(100);
  DebugSerial.end();
  delay(100);
  phSerial.begin(9600);
  delay(100);

  for (int i = 0; i < 100; i++) {
    char c = phSerial.read();
    if (c == 'P') {
      count = 1;
    }
    if ((count >= 1) && (count <= 7)) {
      ph_value[count1] = c;
      count1++;
      count++;
    }
  }

  count1 = 0;
  delay(100);
  phSerial.end();
  delay(100);
  DebugSerial.begin(9600);
  delay(100);

  Blynk.virtualWrite(V9, ph_value);
  count = 0;
}

// ──────────────────────────────────────────────
//  Utility
// ──────────────────────────────────────────────

void serialFlush() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
}
