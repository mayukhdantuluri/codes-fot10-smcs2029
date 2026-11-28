/*
SMCS 2029 | Grade 10 | Foundations of Technology A
Falcon Wing - Buttons

Block X | Group 3
Group Members: Mayukh Dantuluri, Edward Hou, Dez Murdock

Last Edited on 2026-11-28, 08:35 UTC-5
*/

// Summon the Servo class to use the Servo features
#include <Servo.h>
Servo myServo;

// Pin constants
const int MYOWARE_PIN = A0; // Connect MyoWare 'ENV' (or SIG) pin to A0
const int SERVO_PIN = 9; // Green wire from SpringRC SM-S3317SR Servo Motor into D9, Blue wire into 5V, Black wire into GND

// Servo signal values for SpringRC SM-S3317SR
const int SPEED_STOP = 87; 
const int SPEED_CONSTANT = 10; 
const int SPEED_0 = (SPEED_STOP - SPEED_CONSTANT); // Open hand (counter-clockwise)
const int SPEED_1 = (SPEED_STOP + SPEED_CONSTANT); // Close hand (clockwise)
const int ROTATE_DURATION = 250; // Amount of time (ms) it rotates in either direction

// MyoWare Threshold & State Variables
const int THRESHOLD = 400; // Muscle flex threshold (0-1023), to be modified using readings from the Serial Monitor
bool lastAboveThreshold = false; // Tracks previous muscle state
bool stateToggled = false; // false = 0 (open), true = 1 (close)

void setup() {
  pinMode(MYOWARE_PIN, INPUT);
  Serial.begin(9600); // Start communcations with the Serial Monitor
  
  // Servo attached to D9 and set initial state to STOPPED
  myServo.attach(SERVO_PIN);
  myServo.write(SPEED_STOP);
}

void loop() {
  int sensorValue = analogRead(MYOWARE_PIN); // Read the processed muscle voltage from the MyoWare
  Serial.println(sensorValue); // Print readings to help calibrate THRESHOLD

  bool isFlexed = (sensorValue > THRESHOLD); // Check if muscle voltage crosses above THRESHOLD

  // Detect if the arm flexes (1) or relaxes (0)
  if (!lastAboveThreshold && isFlexed) {
    stateToggled = !stateToggled; // Switch state between 1 and 0
    Serial.println(stateToggled ? "1" : "0");
    
    if (stateToggled) {
      // 1 = Close hand, rotate clockwise
      myServo.write(SPEED_1);
      delay(ROTATE_DURATION);
      myServo.write(SPEED_STOP);
    } else {
      // 0 = Open hand, rotate counter-clockwise
      myServo.write(SPEED_0);
      delay(ROTATE_DURATION);
      myServo.write(SPEED_STOP);
    }

    delay(300); // Debounce delay to prevent a single flex from double-triggering
  }

  lastAboveThreshold = isFlexed;
  delay(20); // Small loop stabilization delay
}
