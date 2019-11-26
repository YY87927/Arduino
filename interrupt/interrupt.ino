int ledPin = 3;
volatile byte state = LOW;

void setup(){
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
//  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), glow, CHANGE);
}

void loop(){
  digitalWrite(ledPin, state);
}

void glow(){
  delay(500);
  state = !state;
  delay(500);
}
