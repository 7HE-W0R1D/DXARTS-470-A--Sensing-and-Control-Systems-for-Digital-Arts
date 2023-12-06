#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 5;

// < is P1, > is P2, / is P3

char keys[ROWS][COLS] = {
    {'/', '1', '2', '3', ')'},
    {'>', '4', '5', '6', 'L'},
    {'<', '7', '8', '9', 'M'},
    {'(', '*', '0', '#', 'F'}};

String multiEnabled = "0123456789";
String keyStringArray[10] = {
    "0Z.",
    "1", "2ABC", "3DEF",
    "4GHI", "5JKL", "6MNO",
    "7PQRS", "8TUV", "9WXY."};

byte rowPins[ROWS] = {9, 10, 13, 12};
byte colPins[COLS] = {8, 5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
int multiPressDelay = 1000;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  readKeypadInput("Enter a number: ");
  delay(100);
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