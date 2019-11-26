int ledPin = 3;
int potPin = A0;

void setup() {
  // setup pin modes
  pinMode(ledPin, OUTPUT);                  
  pinMode(potPin, INPUT);
}

void loop() {
  // read the value of the pot and store it as potValue
  int potValue = analogRead(potPin);
  
  // turn led on and wait for the time equal to potValue
  digitalWrite(ledPin, HIGH);
  delay(potValue);
  
  // re-read the value of the pot and store it as potValue
  potValue = analogRead(potPin);

  // turn led off and wait for the time equal to potValue
  digitalWrite(ledPin, LOW);
  delay(potValue);
}
