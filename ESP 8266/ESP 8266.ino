#include <SoftwareSerial.h>

// SoftwareSerial espSerial(A0, A1); // RX, TX
SoftwareSerial espSerial(A1, A0); // RX, TX

String ssid_home = "MSI7C94";
String password_home = "MSIB550M";
String ssid = "UW MPSK";
String password = ":$SpEL7<*7";

void setup()
{
  Serial.begin(9600);
  espSerial.begin(9600);
  delay(500);
  reset();
  delay(500);

  Serial.println("Connecting to WiFi...");
  // espSerial.println("AT+CWJAP_CUR=\"" + ssid_home + "\",\"" + password_home + "\"");
  espSerial.println("AT+CWJAP_CUR=\"" + ssid + "\",\"" + password + "\"");
  delay(4000);

  String response = readESPSerial();
  Serial.println(response);

  if (response.indexOf("CONNECTED") != -1 || response.indexOf("GOT IP") != -1 || response.indexOf("OK") != -1
  || response.indexOf("WIFI CON") != -1)
  {
    Serial.println("Connected to WiFi!");
  }
  else
  {
    Serial.println("Failed to connect to WiFi! \nPlease reset the ESP8266 and try again.");
    // for (;;);
  }

  // Serial.println("Getting IP Address");
  // espSerial.println("AT+CIPSTA_CUR?");
  // delay(2000);
  // String ipStr = readESPSerial();
  // Serial.println(ipStr);
  // String ipAddr = ipStr.substring(ipStr.indexOf("\"") + 1, ipStr.lastIndexOf("\""));
  // ipAddr.replace("\r", "");
  // ipAddr.replace("\"", "");
  // Serial.println("IP get: " + ipAddr + " END");
}

void loop()
{
  // String siteURL = serialPrompt("Please enter your PING target: ");
  // Serial.println("pinging " + siteURL + ": ");
  // int siteDelay = pingSite(siteURL);
  // Serial.println(siteDelay);
  // // Serial.println("pinging google.com: ");
  // // int siteDelay = pingSite("google.com");
  // // Serial.println(siteDelay);
  // delay(500);
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

int pingSite(String siteURL) {
  espSerial.println("AT+PING=\""+ siteURL +"\"");
  delay(1000);
  String response = readESPSerial();
  Serial.println("response: " + response);


  if (response.indexOf("OK") != -1) {
    String siteDelay = response.substring(response.lastIndexOf("+") + 1, response.indexOf("OK") - 1);
    siteDelay.replace("\r", "");
    siteDelay.replace("\n", "");
    Serial.println("Ping delay: " + siteDelay + "ms");
    
    return siteDelay.toInt();
  } else {
    return -1;
  }
}

String serialPrompt(String prompt) {
    Serial.println("Please enter your PING target: ");

  while(Serial.available() == 0){
  }

  String input = Serial.readString();
  return input;
}

void reset() {
  Serial.println("reset");
  espSerial.println("AT+RST");
  delay(1000);
  if(espSerial.find("OK") ) Serial.println("Module Reset");
}