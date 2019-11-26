void setup() {
  // put your setup code here, to run once:

  
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("A0: ");
  Serial.print(analogRead(A0));
  Serial.print(", A1: ");
  Serial.print(analogRead(A1));
  Serial.println();
  
  digitalWrite(2, 1);
  digitalWrite(3, 1);
  digitalWrite(4, 0);
  digitalWrite(5, 1);
  digitalWrite(6, 0);
  digitalWrite(7, 1);
}
