#include <Arduino.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

const int buzzerPin = 1;
const int analogPin = A1;

const float MAX_V = 4.2;
const float LOW_V = 3.6;
const float CRITICAL_V = 3.2;

const unsigned short MAX_L = 1023;
const unsigned short LOW_L = MAX_L * (LOW_V / MAX_V);
const unsigned short CRITICAL_L = MAX_L * (CRITICAL_V / MAX_V);

const unsigned short SLEEP_CYCLES = 450;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(analogPin, INPUT);
  analogReference(EXTERNAL);
}

void beep() {
  digitalWrite(buzzerPin, HIGH);
  delay(500);
  digitalWrite(buzzerPin, LOW);
}

unsigned short voltage_level() {
  power_adc_enable();
  analogRead(analogPin);
  delay(5);
  int sensorValue = analogRead(analogPin);
  power_adc_disable();
  return sensorValue;
}

void loop() {
  unsigned short v_level = voltage_level();

  if (v_level <= CRITICAL_L) {
    beep();
    delay(100);
    beep();
  } else if (v_level <= LOW_L) {
    beep();
  }
  for (unsigned short i = 0; i < SLEEP_CYCLES; i++) {
    wdt_enable(WDTO_8S);
    WDTCR |= (1 << WDIE);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_bod_disable();
    sleep_cpu();
    sleep_disable();
    wdt_disable();
  }
}
