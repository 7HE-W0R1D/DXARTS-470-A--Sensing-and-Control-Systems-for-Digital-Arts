#include <SoftwareSerial.h>
#include <Keypad.h>
#include <Wire.h>
#include <SerLCD.h>

// LCD
SoftwareSerial lcdSerial(A4, A5); // RX, TX
SerLCD lcd;

// Wifi
SoftwareSerial espSerial(A1, A0); // RX, TX
String ssid_home = "BreakfastBerry";
String password_home = "N;9263k2";
String ssid_x13 = "ThinkPad";
String password_x13 = "AMD4750u";
String ssid = "UW MPSK";
String password = ":$SpEL7<*7";

// Buzzer
int buzzerPin = 11; // set the buzzer pin
int frequency = 0; // initialize the frequency variable

static int Tones_simple[] ={31, 33, 37, 41, 44, 49, 55, 62, 65, 73, 82, 87, 98, 110, 123, 131, 147, 165,
 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784, 880, 988, 1047};

// Keypad
const byte ROWS = 4;
const byte COLS = 5;

// Wiring: 2 3 4 5 8 9 10 12 || 13

// < is P1, > is P2, / is P3
char keys[ROWS][COLS] = {
//          8    5    4    3    2
/* 9  */  {'/', '1', '2', '3', ')'},
/* 10 */  {'>', '4', '5', '6', 'L'},
/* 13 */  {'<', '7', '8', '9', 'M'},
/* 12 */  {'(', '*', '0', '#', 'F'}
};

String multiEnabled = "0123456789";
String keyStringArray_Capital[10] = {
  "0Z.",
  "1", "2ABC", "3DEF",
  "4GHI", "5JKL", "6MNO",
  "7PQRS", "8TUV", "9WXY"
};

String keyStringArray[10] = {
  "0z.",
  "1", "2abc", "3def",
  "4ghi", "5jkl", "6mno",
  "7pqrs", "8tuv", "9wxy"
};

byte rowPins[ROWS] = {9, 10, 13, 12};
byte colPins[COLS] = {8, 5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
int multiPressDelay = 1000;
String result = "";

// ASCII
String ASCIIStr = "";
char intToASCII(int , boolean = true);

String serialPrompt(String = "Please enter your PING target: ");

// LED
int ledUPin = 6; // Upper LED, PWM
int ledDPin = 7; // Lower LED, no PWM

void setup()
{
  pinMode(buzzerPin, OUTPUT); // set the buzzer pin as an output
  pinMode(ledUPin, OUTPUT);
  pinMode(ledDPin, OUTPUT);
  Serial.begin(9600);

  lcdSerial.begin(9600);
  // Initialize the LCD
  lcd.begin(lcdSerial);
  // Clear the LCD screen
  lcdClear();
  delay(500);

  espSerial.begin(9600);
  espSerial.listen();
  delay(500);
  digitalWrite(ledUPin, HIGH);
  delay(100);
  digitalWrite(ledDPin, HIGH);
  delay(500);
  digitalWrite(ledUPin, LOW);
  delay(100);
  digitalWrite(ledDPin, LOW);

  // Serial.println("Setting ESP8266 to station mode...");
  lcd.print("Setting ESP8266");
  lcd.setCursor(0, 1);
  lcd.print("to station mode...");
  espSerial.println("AT+CWMODE=1");
  delay(1000);

  lcdClear();
  // Serial.println("Connecting to WiFi...");
  lcd.print("WIFI Connecting");
  delay(50);
  espSerial.println("AT+CWJAP_CUR=\"" + ssid_home + "\",\"" + password_home + "\"");
  // espSerial.println("AT+CWJAP_CUR=\"" + ssid_x13 + "\",\"" + password_x13 + "\"");
  // espSerial.println("AT+CWJAP_CUR=\"" + ssid + "\",\"" + password + "\"");
  delay(4000);

  lcdClear();
  String response = readESPSerial();
  // Serial.println(response);

  if (response.indexOf("CONNECTED") != -1 || response.indexOf("GOT IP") != -1 || response.indexOf("OK") != -1
  || response.indexOf("WIFI CON") != -1)
  {
    // Serial.println("Connected to WiFi!");
    lcd.print("WIFI Connected");
    noTone(buzzerPin); // stop the tone
    tone(buzzerPin, Tones_simple[10]); // generate the tone with the specified frequency
    digitalWrite(ledUPin, HIGH);
    delay(50); // wait for 50 milliseconds
    noTone(buzzerPin); // stop the tone
    digitalWrite(ledUPin, LOW);
    delay(50); // wait for 50 milliseconds
    tone(buzzerPin, Tones_simple[10]); // generate the tone with the specified frequency
    digitalWrite(ledUPin, HIGH);
    delay(50); // wait for 50 milliseconds
    noTone(buzzerPin); // stop the tone
    digitalWrite(ledUPin, LOW);
  }
  else
  {
    // Serial.println("Failed to connect to WiFi! \nPlease reset the ESP8266 and try again.");
    // for (;;);
    lcd.print("WIFI Failed");
    tone(buzzerPin, Tones_simple[3]); // generate the tone with the specified frequency
    delay(500); // wait for 100 milliseconds
    noTone(buzzerPin); // stop the tone
  }

  delay(3000);

  lcdClear();
  // Serial.println("Getting IP Address");
  lcd.print("Getting IP Addr");
  espSerial.println("AT+CIPSTA_CUR?");
  delay(2000);
  String ipStr = readESPSerial();
  // Serial.println(ipStr);
  String ipAddr = ipStr.substring(ipStr.indexOf("\"") + 1, ipStr.lastIndexOf("\""));
  ipAddr.replace("\r", "");
  ipAddr.replace("\"", "");
  // Serial.println("IP get: " + ipAddr + " END");
  lcdClear();
  lcd.print("IP Addr: ");
  lcd.setCursor(0, 1);
  lcd.print(ipAddr);
  randomSeed(analogRead(A2));
  delay(3000);
}

void loop()
{
  lcdClear();
  // Serial.println("Welcome to the W3Phone!");
  lcd.print("Welcome to the ");
  lcd.setCursor(0, 1);
  lcd.print("W3Phone!");
  delay(3000);
  lcdClear();

  ASCIIStr = "";
  String siteURL = readKeypadInput("Comm w/ internet!");
  delay(1000);
  siteURL.toLowerCase();
  // Serial.println("Communicating with " + siteURL + ": ");
  lcdClear();
  lcd.print("Comm w/");
  lcd.setCursor(0, 1);
  lcd.print("http://" + siteURL);
  delay(1000);
  lcdClear();
  lcd.print("Response:");
  lcd.setCursor(0, 1);
  for (int i = 0; i < 15; i++) {
    // Serial.println("pinging " + siteURL + ": ");
    int siteDelay = pingSite(siteURL);

    char ascii = intToASCII(siteDelay);
    ASCIIStr += ascii;
    // Serial.println("Response: " + ASCIIStr);
    // Serial.println(siteDelay);
    lcd.write(ascii);

    delay(50); // CANNOT DELETE THIS DELAY
    frequency = convertFreq(ConvNumber(siteDelay));
    // Serial.println(frequency);
    noTone(buzzerPin); // stop the tone
    tone(buzzerPin, frequency); // generate the tone with the specified frequency
    delay(250); // wait for 100 milliseconds

  }
  noTone(buzzerPin); // stop the tone
  delay(3000);
  lcdClear();
  lcd.print("Comm Complete");
  delay(1000);
  lcdClear();
  lcd.print("Thank you for");
  lcd.setCursor(0, 1);
  lcd.print("using W3Phone!");
  delay(3000);
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
  delay(1500);
  String response = readESPSerial();
  // Serial.println("response: " + response);

  if (response.indexOf("OK") != -1) {
    String siteDelay = response.substring(response.lastIndexOf("+") + 1, response.indexOf("OK") - 1);
    siteDelay.replace("\r", "");
    siteDelay.replace("\n", "");
    // Serial.println("Ping delay: " + siteDelay + "ms");
    
    return siteDelay.toInt();
  } else {
    return -1;
  }
}

String serialPrompt(String prompt = "Please enter your PING target: ") {
  Serial.println(prompt);

  while(Serial.available() == 0){
  }

  String input = Serial.readString();
  return input;
}

String readKeypadInput(String prompt)
{
  String result = "";
  String displayString = "";
  String prefix = "http://";
  // Serial.println(prompt);

  lcd.print(prompt);
  lcd.setCursor(0, 1);
  lcd.print(prefix);
  for (;;)
  {
    static unsigned long lastMillis = 0;
    static char lastKey = NO_KEY;
    static int keyCount = 0;
    char key = keypad.getKey();

    if (key != NO_KEY)
    {
      // Beep when key is pressed
      int keyStringIndex = multiEnabled.indexOf(key);
      int frequency = Tones_simple[keyStringIndex * 3 + 10];
      tone(buzzerPin, frequency); // generate the tone with the specified frequency
      digitalWrite(ledUPin, HIGH);
      delay(30);
      noTone(buzzerPin); // stop the tone
      digitalWrite(ledUPin, LOW);

      // Special keys first
      if (key == '#')
      {
        // Serial.println("Final result: " + result);
        displayString = prefix + result;
        displayString = displayString.substring(0, 16);
        lcdClear();
        lcd.print("Entered:");
        lcd.setCursor(0, 1);
        lcd.print(displayString);
        return result;
      }

      if (key == '*')
      {
        result = result.substring(0, result.length() - 1);
        // Serial.println("Result: " + result);
        displayString = prefix + result;
        displayString = displayString.substring(0, 16);
        lcdClear();
        lcd.print(prompt);
        lcd.setCursor(0, 1);
        lcd.print(displayString);
        continue;
      }

      if (key == '/')
      {
        result = "portfolio.breakfastberry.live";
        displayString = prefix + result;
        displayString = displayString.substring(0, 16);
        lcdClear();
        lcd.print(prompt);
        lcd.setCursor(0, 1);
        lcd.print(displayString);
        return result;
      }

      if (key == '>') {
        result = "bing.com";
        displayString = prefix + result;
        displayString = displayString.substring(0, 16);
        lcdClear();
        lcd.print(prompt);
        lcd.setCursor(0, 1);
        lcd.print(displayString);
        return result;
      }

      if (key == '<') {
        result = "8.8.8.8";
        displayString = prefix + result;
        displayString = displayString.substring(0, 16);
        lcdClear();
        lcd.print(prompt);
        lcd.setCursor(0, 1);
        lcd.print(displayString);
        return result;
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
        result += key;

      }

      // Serial.println("Result: " + result);
      displayString = prefix + result;
      displayString = displayString.substring(0, 16);
      lcdClear();
      lcd.print(prompt);
      lcd.setCursor(0, 1);
      lcd.print(displayString);
    }
  }
}

char intToASCII(int num, boolean charOnly = true)
{
  int mapped = 0;
  if (charOnly)
  {

    if (num <= 0)
    {
      return ' ';
    }

    mapped = (abs(num) % 64) + 64;

    if ((mapped >= 91 && mapped <= 96) ||
       (mapped >= 123 && mapped <= 126) ||
       (mapped == 0))
    {
      return ' ';
    }
  }
  else {
    mapped = abs(num) % 128;
  }

  // Serial.println(mapped);
  char result = mapped;
  return result;
}

int convertFreq(int inputFreq){
  int frequency = inputFreq;
  // int digit2 = inputFreq % 10 + 1;
  // frequency = (inputFreq * digit2);
  frequency = 1047 * (sin(1.618 * (frequency - (PI / 2))) + 1) / 2;
  // Serial.print(frequency);
  // Serial.print(" ");
  int toneFreq = matchTone(frequency) * 0.618;
  // Serial.println(toneFreq);
  return toneFreq;
}

int matchTone(int inputTone) {
  for (int i = 0; i < sizeof(Tones_simple) - 1; i++) {
    if (inputTone <= (Tones_simple[i] + Tones_simple[i + 1]) / 2) {
      return Tones_simple[i];
    }
  }
  return Tones_simple[sizeof(Tones_simple) - 1];
}

int prevNumber = -1;
int prevResult = -1;
int ConvNumber (int Input) {
    if (prevNumber == Input) {
        return prevResult;
    } else {
        prevNumber = Input;
        prevResult = ConvNumber_Map(Input);
        return prevResult;
    }
}

int ConvNumber_Map(int Input) {
    const int RANGE = 6;
    int randNumber = random(RANGE);
    return Input + randNumber - (RANGE - 1) / 2;
}

void reset() {
  Serial.println("reset");
  espSerial.println("AT+RST");
  delay(1000);
  if(espSerial.find("OK") ) Serial.println("Module Reset");
}

void lcdClear() {
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 0);
}