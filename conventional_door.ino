#include <Servo.h>

Servo doorServo;

// HC-SR04 pins
const int trigPin = 7;
const int echoPin = 8;

// 1 foot in cm
const float detectionThreshold = 30.48;

bool doorOpen = false;
unsigned long doorOpenedAt = 0;
const unsigned long doorOpenDuration = 10000; // 10 seconds

void setup() {
  Serial.begin(9600);

  doorServo.attach(9);
  doorServo.write(0); // Start closed

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return -1;
  return (duration * 0.0343) / 2;
}

void openDoor() {
  doorServo.write(180);
  doorOpen = true;
  doorOpenedAt = millis();
}

void closeDoor() {
  doorServo.write(0);
  doorOpen = false;
}

void loop() {
  float distance = getDistance();

  if (distance > 0 && distance < detectionThreshold && !doorOpen) {
    openDoor();
  }

  if (doorOpen && (millis() - doorOpenedAt >= doorOpenDuration)) {
    closeDoor();
  }

  delay(100);
}