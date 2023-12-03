#include <SoftwareSerial.h>

// SoftwareSerial espSerial(6, 7); // RX, TX
SoftwareSerial espSerial(A1, A0); // RX, TX

String ssid = "MSI7C94";
String password = "MSIB550M";

void setup()
{
  Serial.begin(115200);
  espSerial.begin(9600);
  delay(500);

  // Serial.println("Getting MAC Address...");
  // espSerial.println("AT+CIPSTAMAC_DEF?");

  Serial.println("Resetting ESP8266...");
  espSerial.println("AT+RESTORE");

  // Serial.println("Setting MAC Address...");
  // espSerial.println("AT+CIPSTAMAC_DEF=\"88:03:f6:43:49:33\"");

  delay(5000);

  String response = readESPSerial();
  Serial.println(response);
}

void loop() {
}

String readESPSerial() {
  String response = "";
  while (espSerial.available()) {
    char c = espSerial.read();
    response += c;
  }
  return response;
}