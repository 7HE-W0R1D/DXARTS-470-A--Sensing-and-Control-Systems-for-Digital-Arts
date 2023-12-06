
static int Tones_simple[] ={31, 33, 37, 41, 44, 49, 55, 62, 65, 73, 82, 87, 98, 110, 123, 131, 147, 165,
 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784, 880, 988, 1047};

static int Tones[] = {31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117,
 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 
 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047};

int buzzerPin = 11; // set the buzzer pin

void setup() {
  pinMode(buzzerPin, OUTPUT); // set the buzzer pin as an output
  Serial.begin(9600); // initialize serial communication
}

void loop() {
  for (int i = 0; i < 10; i++) {
    int r1 = random(10, 20);
    int toneFreq = convertFreq(r1);
    tone(buzzerPin, toneFreq); // generate the tone with the specified frequency
    delay(500); // wait for 500 milliseconds
    noTone(buzzerPin); // stop the tone
  }
}

int convertFreq(int inputFreq){
  int frequency = inputFreq;
  // int digit2 = inputFreq % 10 + 1;
  // frequency = (inputFreq * digit2);
  frequency = 1047 * (sin(1.618 * (frequency - (PI / 2))) + 1) / 2;
  Serial.print(frequency);
  Serial.print(" ");
  int toneFreq = matchTone(frequency);
  Serial.println(toneFreq);
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