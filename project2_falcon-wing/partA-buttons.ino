/*
SMCS 2029 | Grade 10 | Foundations of Technology A
Falcon Wing - Buttons

Block X | Group 3
Group Members: Mayukh Dantuluri, Edward Hou, Dez Murdock

Last Edited on 2026-11-13, 17:40 UTC-5
*/

// Summon the Servo class to use the Servo features
#include <Servo.h>
Servo myServo;

// Pin constants
const int BUTTON_PIN = 2; // Yellow wire from SunFounder Button Module 2.0 into D2, Red wire into 3.3V, Black wire into GND
const int SERVO_PIN = 9; // Green wire from SpringRC SM-S3317SR Servo Motor into D9, Blue wire into 5V, Black wire into GND

// Servo signal values for SpringRC SM-S3317SR (It doesn't understand angles, just uses direction and speed (0-180))
const int SPEED_STOP = 87; // 90 is supposed to be the default stop value but some motors could have a offset value
const int SPEED_CONSTANT = 15; // Constant speed to add or subtract from stopping position
const int SPEED_CW = (SPEED_STOP + SPEED_CONSTANT); // Speed to close hand, use numbers higher than SPEED_STOP for clockwise rotation
const int SPEED_CCW = (SPEED_STOP - SPEED_CONSTANT); // Speed to open hand, use numbers lower than SPEED_STOP for counterclockwise rotation
const int ROTATE_DURATION = 500; // Amount of time (ms) it rotates in either direction

// Boolean variables to store the toggle state
bool buttonToggled = false;
bool lastReading = HIGH;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set as input
  Serial.begin(9600); // Start communications with the Serial Monitor

  // Servo attached to D9 and set initial state to STOPPED
  myServo.attach(SERVO_PIN);
  myServo.write(SPEED_STOP);
}

void loop() {
  int reading = digitalRead(BUTTON_PIN); // Read the button state from D2

  // Detect release: switches between LOW (pressed) and HIGH (released)
  if (lastReading == LOW && reading == HIGH) {
    buttonToggled = !buttonToggled; // Switch the boolean value only once no matter how long I hold it
    Serial.println(buttonToggled ? "1" : "0"); // 1 = close the hand, 0 = open the hand
    
    if (buttonToggled) {
      // 1 = Close hand, rotate clockwise
      myServo.write(SPEED_CW);
      delay(ROTATE_DURATION);
      myServo.write(SPEED_STOP);
    } else {
      // 0 = Open hand, rotate counter-clockwise
      myServo.write(SPEED_CCW);
      delay(ROTATE_DURATION);
      myServo.write(SPEED_STOP);
    }
  }

  lastReading = reading;
}
