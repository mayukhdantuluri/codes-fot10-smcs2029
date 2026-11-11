/*
SMCS 2029 | Grade 10 | Foundations of Technology A
Falcon Wing - Button Code Test

Block X | Group 3
Group Members: Mayukh Dantuluri, Edward Hou, Dez Murdock

Last Edited on 2026-11-11, 18:50 UTC-5
*/

// Pin constants
const int BUTTON_PIN = 2;  // Yellow wire from button module

// Boolean variables to store the toggle state
bool buttonToggled = false;
bool lastReading = HIGH;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set as input
  Serial.begin(9600); // Start communications with the Serial Monitor
}

void loop() {
  int reading = digitalRead(BUTTON_PIN); // Read the button state

  // Detect release: switches between LOW (pressed) and HIGH (released)
  if (lastReading == LOW && reading == HIGH) {
    buttonToggled = !buttonToggled; // Switch the boolean value
    Serial.println(buttonToggled ? "1" : "0"); // Whenever I press the button, it changes only once no matter how long I hold it
  }

  lastReading = reading;
}
