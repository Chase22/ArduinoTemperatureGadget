#include <Adafruit_BME280.h>

#include <Adafruit_BME280.h>

#include <FlexiTimer2.h>

#define PinTime 0
#define PinTempUnit 0
#define PinShow 0

float temp;
float humid;
float pressure;

bool last_state_time;
bool last_state_unit;
bool last_state_show;

Adafruit_BME280 bme;

void readValues() {
  temp = bme.readTemperature();
  humid = bme.readHumidity();
  pressure = bme.readPressure();
}

void setup() {
  status = bme::begin();

  if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
  }

  setPinMode(PinTime, INPUT);
  setPinMode(PinTempUnit, INPUT);
  setPinMode(PinShow, INPUT_PULLUP);
  
  FlexiTimer2::set(100, readValues());
}

void loop() {
  
}
