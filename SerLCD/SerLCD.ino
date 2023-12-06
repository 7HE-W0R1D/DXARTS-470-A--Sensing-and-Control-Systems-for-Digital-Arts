#include <Wire.h>
#include <SerLCD.h>
#include <SoftwareSerial.h>

SoftwareSerial espSerial(A1, A0); // RX, TX
SoftwareSerial lcdSerial(A4, A5); // RX, TX

// Create an instance of the SerLCD class
SerLCD lcd;

void setup() {
  Serial.begin(9600);
  lcdSerial.begin(9600);
  // Initialize the LCD
  lcd.begin(lcdSerial);
  delay(500);
  // Clear the LCD screen

  espSerial.begin(9600);
  espSerial.listen();
  
  delay(500);
  lcd.print("Hello, World!");
  // Serial.println("Serial!");
  lcd.print("Wow");
}

void loop() {
  lcdClear();
  lcd.print("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
  delay(500);
  // Set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // lcd.setCursor(0, 1);
  // Print the number of seconds since reset:

}

void lcdClear() {
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 0);
}