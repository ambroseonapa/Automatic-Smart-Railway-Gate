// Basic detection and closing the gate
// include the required libraries
#include <Servo.h>

// define the pins
#define servoPin 9
#define sensorPin 10

// initialize the servo and sensor objects
Servo servo;
int sensorState;

void setup() {
  // initialize the servo and sensor pins
  servo.attach(servoPin);
  pinMode(sensorPin, INPUT);
}

void loop() {
  // read the state of the sensor
  sensorState = digitalRead(sensorPin);

  if (sensorState == HIGH) {
    // if the sensor detects an object, close the railway gate
    servo.write(0);
    delay(5000);
  } else {
    // if the sensor doesn't detect an object, open the railway gate
    servo.write(90);
    delay(5000);
  }
}
