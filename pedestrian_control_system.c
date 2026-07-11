#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD Configuration
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin Definitions
const int RED_LED = 4;
const int YELLOW_LED = 9;
const int GREEN_LED = 10;
const int BUTTON_PIN = 6;

// Pedestrian Counter
int pedestrianCount = 0;

void setup() {
  // Configure LED pins
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // Configure Push Button using internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Initial Traffic Light State
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  displayCount();
}

void loop() {

  // Button pressed (LOW because INPUT_PULLUP is used)
  if (digitalRead(BUTTON_PIN) == LOW) {

    // Debounce delay
    delay(50);

    // Confirm button is still pressed
    if (digitalRead(BUTTON_PIN) == LOW) {

      // Wait until button is released
      while (digitalRead(BUTTON_PIN) == LOW);

      delay(50);

      runTrafficSequence();
    }
  }
}

// ------------------------------
// Traffic Light Sequence
// ------------------------------
void runTrafficSequence() {

  // Green OFF
  digitalWrite(GREEN_LED, LOW);

  // Yellow ON (2 seconds)
  digitalWrite(YELLOW_LED, HIGH);
  delay(2000);

  digitalWrite(YELLOW_LED, LOW);

  // Red ON
  digitalWrite(RED_LED, HIGH);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PLEASE CROSS");
  lcd.setCursor(0, 1);
  lcd.print("SAFELY");

  delay(6000);

  // Count pedestrian
  pedestrianCount++;

  // Red OFF
  digitalWrite(RED_LED, LOW);

  // Yellow ON (2 seconds)
  digitalWrite(YELLOW_LED, HIGH);
  delay(2000);

  digitalWrite(YELLOW_LED, LOW);

  // Return to Green
  digitalWrite(GREEN_LED, HIGH);

  // Display Updated Count
  displayCount();
}

// ------------------------------
// LCD Display Function
// ------------------------------
void displayCount() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Pedestrians:");

  lcd.setCursor(0, 1);
  lcd.print("Count: ");
  lcd.print(pedestrianCount);
}
