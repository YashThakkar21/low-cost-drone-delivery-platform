#include <Servo.h>

Servo doorServo1;
Servo doorServo2;

// HC-SR04 pins
const int trigPin = 7;
const int echoPin = 8;

// 1 foot in cm
const float detectionThreshold = 30.48;

bool doorsOpen = false;
unsigned long doorOpenedAt = 0;
const unsigned long doorOpenDuration = 10000; // 10 seconds

void setup() {
  Serial.begin(9600);

  doorServo1.attach(9);
  doorServo2.attach(10);

  // Start with doors closed
  doorServo1.write(0);
  doorServo2.write(180); // Mirrored for opposite side of door

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println("Door system ready.");
}

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
  if (duration == 0) return -1;
  return (duration * 0.0343) / 2;
}

void openDoors() {
  doorServo1.write(180);
  doorServo2.write(0); // Mirrored open position
  doorsOpen = true;
  doorOpenedAt = millis();
  Serial.println("Doors OPENED");
}

void closeDoors() {
  doorServo1.write(0);
  doorServo2.write(180); // Mirrored closed position
  doorsOpen = false;
  Serial.println("Doors CLOSED");
}

void loop() {
  float distance = getDistance();

  // If something is within 1 foot and doors are closed, open them
  if (distance > 0 && distance < detectionThreshold && !doorsOpen) {
    openDoors();
  }

  // If doors are open and 10 seconds have passed, close them
  if (doorsOpen && (millis() - doorOpenedAt >= doorOpenDuration)) {
    closeDoors();
  }

  delay(100);
}