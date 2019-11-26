void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(2) == HIGH){
    Serial.println("button1");
  }
  if(digitalRead(3) == HIGH){
    Serial.println("button2");
  }
  if(digitalRead(4) == HIGH){
    Serial.println("button3");
  }
}
