#include <SoftwareSerial.h>

SoftwareSerial espSerial(6, 7); // RX, TX
String ssid = "UW MPSK";
String password = ":$SpEL7<*7";

void setup()
{
  Serial.begin(2400);
  espSerial.begin(9600);
  delay(500);

  Serial.println("Connecting to WiFi...");
  espSerial.println("AT+CWJAP_CUR=\"" + ssid + "\",\"" + password + "\"");
  delay(5000);

  String response = readESPSerial();
  Serial.println(response);

  if (response.indexOf("CONNECTED") != -1 || response.indexOf("GOT IP") != -1)
  {
    Serial.println("Connected to WiFi!");
  }
  else
  {
    Serial.println("Failed to connect to WiFi! \nPlease reset the ESP8266 and try again.");
    // for (;;);
  }

  Serial.println("Getting IP Address");
  espSerial.println("AT+CIPSTA_CUR?");
  delay(2000);
  String ipStr = readESPSerial();
  Serial.println(ipStr);
  String ipAddr = ipStr.substring(ipStr.indexOf("\"") + 1, ipStr.lastIndexOf("\""));
  ipAddr.replace("\r", "");
  ipAddr.replace("\"", "");
  Serial.println("IP get: " + ipAddr + " END");

  Serial.println("Update firmware");
  espSerial.println("AT+CIUPDATE");
  delay(1000);
  String response2 = readESPSerial();
  Serial.println(response2);
}

void loop() {
  String response2 = readESPSerial();
  Serial.println(response2);
  delay(1000);
}

String readESPSerial() {
  String response = "";
  while (espSerial.available()) {
    char c = espSerial.read();
    response += c;
  }
  return response;
}