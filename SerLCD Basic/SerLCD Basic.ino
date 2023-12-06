void setup() {
    // Start the hardware Serial communication
    Serial.begin(9600);
    
    // Initialize the Serial LCD
    Serial.write(0xFE); // Command prefix
    Serial.write(0x80); // Set cursor to the beginning of the first line
    // Serial.print("Hello, LCD!"); // Display the message on the LCD
}

void loop() {
    // Read data from the hardware Serial
    if (Serial.available()) {
        char data = Serial.read();
        
        // Forward the data to the Serial LCD
        Serial.write(data);
    }
}
