#include <Adafruit_Sensor.h>

#include <Adafruit_BME280.h>

#include <Adafruit_BME280.h>

#include <FlexiTimer2.h>

#define PinTime 0
#define PinTempUnit 0
#define PinShow 0

float temp;
float humid;
float pressure;

int mode = 3;

int state_time;
int last_state_time;

Adafruit_BME280 bme;

void readValues() {
  temp = bme.readTemperature();
  humid = bme.readHumidity();
  pressure = bme.readPressure();
}

void setMode() {
  switch (mode) {
    case 0:
      FlexiTimer2::set(15000, readValues); // call every 15 seconds
      break;
    case 1:
      FlexiTimer2::set(30000, readValues); // call every 30 seconds
      break;
    case 2:
      FlexiTimer2::set(60000, readValues); // call every minute
      break;
    case 3:
      FlexiTimer2::set(300000, readValues); // call every 5 minutes
      break;
    case 4:
      FlexiTimer2::set(900000, readValues); // call every 15 minutes
      break;
    default:
      mode = 0;
      break;
  }
}

void setup() {
  bool status = bme.begin();

  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  pinMode(PinTime, INPUT);
  pinMode(PinTempUnit, INPUT);
  pinMode(PinShow, INPUT);

  setMode();
}

void loop() {
  state_time = digitalRead(PinTime);

  if (state_time != last_state_time) {
    mode++;
    setMode();
  }

}
