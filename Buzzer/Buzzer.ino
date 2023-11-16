
int buzzerPin = 11; // set the buzzer pin
int frequency = 0; // initialize the frequency variable

void setup() {
  pinMode(buzzerPin, OUTPUT); // set the buzzer pin as an output
  Serial.begin(115200); // initialize serial communication
}

void loop() {
  if (Serial.available() > 0) { // check if there is serial input
    frequency = Serial.parseInt(); // read the input as an integer
    tone(buzzerPin, frequency); // generate the tone with the specified frequency
    delay(500); // wait for 500 milliseconds
    noTone(buzzerPin); // stop the tone
  }
}
