
#include <SoftwareSerial.h>

// Define the serial communication pins
#define ESP8266_RX_PIN A1
#define ESP8266_TX_PIN A0

SoftwareSerial espSerial(ESP8266_RX_PIN, ESP8266_TX_PIN); // Create a SoftwareSerial object for ESP8266

void setup() {
  Serial.begin(115200); // Start the serial communication with the computer
  espSerial.begin(9600); // Start the serial communication with the ESP8266
}

void loop() {
    String prompt = serialPrompt("Please enter your Command: ");
    espSerial.println(prompt);  // Send the user input to the ESP8266
    delay(100);
    String response = readESPSerial(); // Read the reply from ESP8266
    Serial.println(response); // Print the reply from ESP8266
    delay(1000);
}


String serialPrompt(String prompt) {
  Serial.println(prompt);

  while(Serial.available() == 0){
  }

  String input = Serial.readString();
  return input;
}

String readESPSerial()
{
  String response = "";
  while (espSerial.available())
  {
    char c = espSerial.read();
    response += c;
  }
  return response;
}
