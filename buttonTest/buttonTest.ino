void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(7)==1){
     Serial.print("**");
     Serial.println();
     delay(500);
  }
}
