void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Hello, This is program to get X Y setpoint value!\r\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("x is: ");
  Serial.print(analogRead(A4));
  Serial.print("    ");
  Serial.print("y is: ");
  Serial.print(analogRead(A5));
  Serial.print("\r\n");
  delay(100);
}
