void setup() {
  // put your setup code here, to run once:
  pinMode(9, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  int x=digitalRead(9);
  //Serial.println(v);
  digitalWrite(13, x);
}
