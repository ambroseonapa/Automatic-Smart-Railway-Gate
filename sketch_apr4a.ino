#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int irSensor1 = 9;  // Pin for IR sensor 1
int irSensor2 = 8;  // Pin for IR sensor 2
int irSensor3 = 7;  // Pin for IR sensor 3
int irSensor4 = 6;  // Pin for IR sensor 4
int greenLed = 10;  // Pin for green LED
int redLed = A0;    // Pin for red LED
int buzzer = A1;    // Pin for buzzer

int thresholdDistance = 100;  // Threshold distance for IR sensor 2

int openPosition = 0;    // Open position for servos
int closePosition = 90;  // Close position for servos

#include <Servo.h>
Servo leftServo1;
Servo leftServo2;
Servo rightServo1;
Servo rightServo2;

void setup() {
  lcd.begin(16, 2);
  pinMode(irSensor1, INPUT);
  pinMode(irSensor2, INPUT);
  pinMode(irSensor3, INPUT);
  pinMode(irSensor4, INPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  leftServo1.attach(13);
  leftServo2.attach(14);
  rightServo1.attach(15);
  rightServo2.attach(16);
  lcd.print("Gate closed");
}

void loop() {
  // Check for train arrival
  if (digitalRead(irSensor1) == HIGH) {
    lcd.clear();
    lcd.print("Train Coming");
    digitalWrite(greenLed, HIGH);
    while (digitalRead(irSensor1) == HIGH) {
      delay(100);
    }
  }

  // Check for train arrival at the threshold distance
  if (digitalRead(irSensor2) == HIGH) {
    lcd.clear();
    lcd.print("Train Arrival");
    digitalWrite(redLed, HIGH);
    tone(buzzer, 1000, 1000);

    // Check for obstacles at the gate
    if (digitalRead(irSensor3) == LOW) {
      // Clear the area before closing the gate
      lcd.clear();
      lcd.print("Clear");
      delay(5000);
      closeGate();
    } else {
      delay(1000);
    }
  } else {
    digitalWrite(redLed, LOW);
    noTone(buzzer);
  }

  // Check for train departure
  if (digitalRead(irSensor4) == HIGH) {
    lcd.clear();
    lcd.print("Gate opening");
    openGate();
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);
    noTone(buzzer);
    while (digitalRead(irSensor4) == HIGH) {
      delay(100);
    }
  }
}

void openGate() {
  leftServo1.write(openPosition);
  leftServo2.write(openPosition);
  rightServo1.write(openPosition);
  rightServo2.write(openPosition);
  delay(2000);
}

void closeGate() {
  leftServo1.write(closePosition);
  leftServo2.write(closePosition);
  rightServo1.write(closePosition);
  rightServo2.write(closePosition);
  lcd.clear();
  lcd.print("Gate closed");
  delay(2000);
}

