const int A = 13;
const int B = 12;
const int C = 11;


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  pinMode(A, OUTPUT);
  digitalWrite(A, HIGH);
  pinMode(B, OUTPUT);
  digitalWrite(B, LOW);
  pinMode(C, INPUT);
  digitalWrite(C, LOW);
  delay(1000);

  pinMode(A, OUTPUT);
  digitalWrite(A, LOW);
  pinMode(B, OUTPUT);
  digitalWrite(B, HIGH);
  pinMode(C, INPUT);
  digitalWrite(C, LOW);
  delay(1000);

  pinMode(A, OUTPUT);
  digitalWrite(A, HIGH);
  pinMode(B, INPUT);
  digitalWrite(B, LOW);
  pinMode(C, OUTPUT);
  digitalWrite(C, LOW);
  delay(1000);

  pinMode(A, OUTPUT);
  digitalWrite(A, LOW);
  pinMode(B, INPUT);
  digitalWrite(B, LOW);
  pinMode(C, OUTPUT);
  digitalWrite(C, HIGH);
  delay(1000);

  pinMode(A, INPUT);
  digitalWrite(A, LOW);
  pinMode(B, OUTPUT);
  digitalWrite(B, HIGH);
  pinMode(C, OUTPUT);
  digitalWrite(C, LOW);
  delay(1000);

  pinMode(A, INPUT);
  digitalWrite(A, LOW);
  pinMode(B, OUTPUT);
  digitalWrite(B, LOW);
  pinMode(C, OUTPUT);
  digitalWrite(C, HIGH);
  delay(1000);
  
  
}
