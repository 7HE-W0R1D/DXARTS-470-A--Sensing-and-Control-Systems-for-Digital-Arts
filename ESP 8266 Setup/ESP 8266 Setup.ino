#include <SoftwareSerial.h>

SoftwareSerial espSerial(6, 7); // RX, TX
String ssid = "BreakfastBerry";
String password = "N;9263k2";

void setup() {
  Serial.begin(2400);
  espSerial.begin(115200);
  delay(500);

  Serial.println("Setting baud rate");
  espSerial.println("AT+UART_DEF=9600,8,1,0,0");
  delay(1000);
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