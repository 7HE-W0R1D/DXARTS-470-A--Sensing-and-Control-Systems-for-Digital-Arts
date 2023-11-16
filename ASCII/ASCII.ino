char intToASCII(int , boolean = true);
int a = 2070;

void setup()
{
  // print the result to the serial monitor
  Serial.begin(115200); // initialize serial communication
  char b = intToASCII(a);
  Serial.print("The ASCII character for the integer ");
  Serial.print(a);
  Serial.print(" is ");
  Serial.println(b);
}

void loop()
{
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
