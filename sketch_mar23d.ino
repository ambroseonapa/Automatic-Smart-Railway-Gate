// Basic 2. Detect, displays and checks whether the obstacle is not present but there is some error
#include <Servo.h>
#include <LiquidCrystal.h>

// define the pins
#define servoPin 9
#define sensorPin 10
#define irSensorPin 3

// initialize the servo and sensor objects
Servo servo;
int sensorState, irSensorState;

// initialize the LCD display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // initialize the servo and sensor pins
  servo.attach(servoPin);
  pinMode(sensorPin, INPUT);
  pinMode(irSensorPin, INPUT);

  // initialize the LCD display
  lcd.begin(16, 2);
  lcd.print("Automatic Railway");
  lcd.setCursor(0, 1);
  lcd.print("System Dashboard");
  delay(3000);
  lcd.clear();
}

void loop() {
  // read the state of the IR sensor
  irSensorState = digitalRead(irSensorPin);

  if (irSensorState == HIGH) {
    // if the train is detected, close the railway gate and display the warning message on the LCD
    lcd.clear();
    lcd.print("Train Detected!");
    lcd.setCursor(0, 1);
    lcd.print("Close Gate");
    delay(1000);
    servo.write(0);
    delay(5000);
  } else {
    // if the train is not detected, check for obstacles and open/close the gate accordingly
    sensorState = digitalRead(sensorPin);

    if (sensorState == HIGH) {
      // if an obstacle is detected, display the warning message on the LCD
      lcd.clear();
      lcd.print("Obstacle Detected!");
      lcd.setCursor(0, 1);
      lcd.print("Stop Train");
      delay(1000);
    } else {
      // if no obstacle is detected, open the gate and display the message on the LCD
      lcd.clear();
      lcd.print("Gate Open");
      lcd.setCursor(0, 1);
      lcd.print("No Train");
      delay(1000);
      servo.write(90);
      delay(5000);
    }
  }
}
