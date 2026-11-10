/*
SMCS 2029 | Grade 10 | Foundations of Technology A
Falcon Wing

Block X | Group 3
Group Members: Mayukh Dantuluri, Edward Hou, Dez Murdock

Last Edited on 2026-11-09, 20:00 UTC-5
*/

#include <Servo.h>

const int BUTTON_PIN = 2; 
const int SERVO_PIN = 9;  

Servo myServo;

int lastButtonState = HIGH; 
bool isOpen = false; // Tracks if the mechanism is "open" or "closed"

// Calibration Time
// Number (in milliseconds) to be adjusted until the motor turns exactly as far as needed
const int RUN_TIME = 1200; 

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  myServo.attach(SERVO_PIN);
  myServo.write(90); // Ensure the motor starts completely stopped
}

void loop() {
  int currentButtonState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    delay(50); // Debounce
    
    isOpen = !isOpen; // Toggle state

    if (isOpen) {
      // 1st Press: Spin forward (e.g., speed 60) for a set time, then stop
      myServo.write(60); 
      delay(RUN_TIME);   
      myServo.write(90); // Stop motor
    } else {
      // 2nd Press: Spin backward (e.g., speed 120) for the same time, then stop
      myServo.write(120); 
      delay(RUN_TIME);    
      myServo.write(90); // Stop motor
    }
  }

  lastButtonState = currentButtonState;
}
