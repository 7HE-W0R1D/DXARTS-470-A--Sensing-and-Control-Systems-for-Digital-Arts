#include <SoftwareSerial.h>
#include <Keypad.h>

// Wifi
SoftwareSerial espSerial(A0, A1); // RX, TX
String ssid_home = "MSI7C94";
String password_home = "MSIB550M";
String ssid = "UW MPSK";
String password = ":$SpEL7<*7";

// Buzzer
int buzzerPin = 11; // set the buzzer pin
int frequency = 0; // initialize the frequency variable

// Keypad
const byte ROWS = 4;
const byte COLS = 5;

// < is P1, > is P2, / is P3
char keys[ROWS][COLS] = {
  {'/', '1', '2', '3', ')'},
  {'>', '4', '5', '6', 'L'},
  {'<', '7', '8', '9', 'M'},
  {'(', '*', '0', '#', 'F'}
};

String multiEnabled = "0123456789";
String keyStringArray[10] = {
  "0Z.",
  "1", "2ABC", "3DEF",
  "4GHI", "5JKL", "6MNO",
  "7PQRS", "8TUV", "9WXY."
};

byte rowPins[ROWS] = {9, 10, 13, 12};
byte colPins[COLS] = {8, 5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
int multiPressDelay = 1000;
String result = "";

// ASCII
String ASCIIStr = "";
char intToASCII(int , boolean = true);

void setup()
{
  pinMode(buzzerPin, OUTPUT); // set the buzzer pin as an output
  Serial.begin(115200);
  espSerial.begin(9600);
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

  Serial.println("Getting IP Address");
  espSerial.println("AT+CIPSTA_CUR?");
  delay(2000);
  String ipStr = readESPSerial();
  Serial.println(ipStr);
  String ipAddr = ipStr.substring(ipStr.indexOf("\"") + 1, ipStr.lastIndexOf("\""));
  ipAddr.replace("\r", "");
  ipAddr.replace("\"", "");
  Serial.println("IP get: " + ipAddr + " END");
}

void loop()
{
  ASCIIStr = "";
  // String siteURL = serialPrompt("Please enter your PING target: ");
  String siteURL = readKeypadInput("Please enter your PING target: ");
  delay(100);
  siteURL.toLowerCase();

  for (int i = 0; i < 10; i++) {
    Serial.println("pinging " + siteURL + ": ");
    int siteDelay = pingSite(siteURL);

    char ascii = intToASCII(siteDelay);
    ASCIIStr += ascii;
    Serial.println("ASCII: " + ASCIIStr);
    Serial.println(siteDelay);
    delay(50); // CANNOT DELETE THIS DELAY
    frequency = siteDelay * 10; // read the input as an integer
    tone(buzzerPin, frequency); // generate the tone with the specified frequency
    delay(500); // wait for 500 milliseconds
    noTone(buzzerPin); // stop the tone
    delay(50);
  }
  delay(50);
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
  // Serial.println("response: " + response);

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

String readKeypadInput(String prompt)
{
  String result = "";
  Serial.println(prompt);
  for (;;)
  {
    static unsigned long lastMillis = 0;
    static char lastKey = NO_KEY;
    static int keyCount = 0;
    char key = keypad.getKey();

    if (key != NO_KEY)
    {
      // Special keys first
      if (key == '#')
      {
        Serial.println("Final result: " + result);
        return result;
      }

      if (key == '*')
      {
        result = result.substring(0, result.length() - 1);
        continue;
      }

      if (key == '/')
      {
        return "google.com";
      }

      // Multi key press key detection
      if (multiEnabled.indexOf(key) >= 0 && key == lastKey && millis() - lastMillis < multiPressDelay)
      {
        // Serial.print("Multi key press: ");

        char finalKey;
        int keyStringIndex = multiEnabled.indexOf(key);
        String keyString = keyStringArray[keyStringIndex];
        finalKey = keyString[keyCount % keyString.length()];
        // Serial.println(finalKey);
        result = result.substring(0, result.length() - 1) + finalKey;

        lastMillis = millis();
        keyCount++;
      }
      else
      {
        lastKey = key;
        lastMillis = millis();
        keyCount = 1;
        // Serial.print("First key press: ");
        // Serial.println(key);
        result += key;
      }

      Serial.println("Result: " + result);
    }
  }
}

char intToASCII(int num, boolean charOnly = true)
{
  int mapped = 0;
  if (charOnly)
  {
    mapped = (abs(num) % 96) + 32;
  }
  else {
    mapped = abs(num) % 128;
  }

  Serial.println(mapped);
  char result = mapped;
  return result;
}
