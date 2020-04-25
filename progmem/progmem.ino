const uint16_t int_array[] PROGMEM = {0, 1, 2, 3, 4};
const uint8_t numElements = sizeof(int_array) / sizeof(int_array[0]);

void setup() {
  uint16_t readValue;
  Serial.begin(115200);
  delay(2000);

  for (uint8_t i = 0; i < numElements; i++)
  {
    readValue = pgm_read_word(&int_array[i]);
    Serial.println(readValue);
  }
  Serial.println("Done");
}

void loop() {}
