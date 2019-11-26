#define A 10
#define B 11
#define C 12
#define D 13

#define PIN_CONFIG 0
#define PIN_STATE 1

#define LED_Num 12
#define LED_Num2 6

int matrix[LED_Num][2][4] = {
  //           PIN_CONFIG                  PIN_STATE
  //    A       B       C      D         A     B    C    D
  { { INPUT_PULLUP, INPUT_PULLUP, OUTPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } },
  { { INPUT_PULLUP, INPUT_PULLUP, OUTPUT, OUTPUT }, { LOW, LOW, HIGH, LOW } }, 
  { { INPUT_PULLUP, OUTPUT, OUTPUT, INPUT_PULLUP }, { LOW, LOW, HIGH, LOW } }, 
  { { INPUT_PULLUP, OUTPUT, OUTPUT, INPUT_PULLUP }, { LOW, HIGH, LOW, LOW } },
  { { OUTPUT, OUTPUT, INPUT_PULLUP, INPUT_PULLUP }, { LOW, HIGH, LOW, LOW } }, 
  { { OUTPUT, OUTPUT, INPUT_PULLUP, INPUT_PULLUP }, { HIGH, LOW, LOW, LOW } },
  { { INPUT_PULLUP, OUTPUT, INPUT_PULLUP, OUTPUT }, { LOW, HIGH, LOW, LOW } },  
  { { INPUT_PULLUP, OUTPUT, INPUT_PULLUP, OUTPUT }, { LOW, LOW, LOW, HIGH } }, 
  { { OUTPUT, INPUT_PULLUP, OUTPUT, INPUT_PULLUP }, { LOW, LOW, HIGH, LOW } },
  { { OUTPUT, INPUT_PULLUP, OUTPUT, INPUT_PULLUP }, { HIGH, LOW, LOW, LOW } },
  { { OUTPUT, INPUT_PULLUP, INPUT_PULLUP, OUTPUT }, { LOW, LOW, LOW, HIGH } }, 
  { { OUTPUT, INPUT_PULLUP, INPUT_PULLUP, OUTPUT }, { HIGH, LOW, LOW, LOW } } 
};

int matrix2[LED_Num][2][3] = {
  //           PIN_CONFIG                  PIN_STATE
  //   B       C      D        B    C    D
  { { OUTPUT, OUTPUT, INPUT_PULLUP }, { LOW, HIGH, LOW } }, 
  { { OUTPUT, OUTPUT, INPUT_PULLUP }, { HIGH, LOW, LOW } }, 
  { { INPUT_PULLUP, OUTPUT, OUTPUT }, { LOW, LOW, HIGH } },
  { { INPUT_PULLUP, OUTPUT, OUTPUT }, { LOW, HIGH, LOW } }, 
  { { OUTPUT, INPUT_PULLUP, OUTPUT }, { HIGH, LOW, LOW } }, 
  { { OUTPUT, INPUT_PULLUP, OUTPUT }, { LOW, LOW, HIGH } }
};

void lightOn( int led ) {
  pinMode( A, matrix[led][PIN_CONFIG][0] );
  pinMode( B, matrix[led][PIN_CONFIG][1] );
  pinMode( C, matrix[led][PIN_CONFIG][2] );
  pinMode( D, matrix[led][PIN_CONFIG][3] );
  digitalWrite( A, matrix[led][PIN_STATE][0] );
  digitalWrite( B, matrix[led][PIN_STATE][1] );
  digitalWrite( C, matrix[led][PIN_STATE][2] );
  digitalWrite( D, matrix[led][PIN_STATE][3] );
}

void lightOn2( int led ) {
  pinMode( B, matrix[led][PIN_CONFIG][0] );
  pinMode( C, matrix[led][PIN_CONFIG][1] );
  pinMode( D, matrix[led][PIN_CONFIG][2] );
  digitalWrite( B, matrix[led][PIN_STATE][0] );
  digitalWrite( C, matrix[led][PIN_STATE][1] );
  digitalWrite( D, matrix[led][PIN_STATE][2] );
}

void setup() {
  Serial.begin(9600);  
 MCUSR |= _BV(PUD);
}

void loop() {
  for( int l = 0; l < LED_Num; l++ ) {
    lightOn( l );
    delay( 1000 );
  }

//  pinMode(B, OUTPUT);
//  pinMode(C, OUTPUT);
//  pinMode(D, INPUT_PULLUP);
//  DDRB = B011000;
//
//  digitalWrite(B, HIGH);
//  digitalWrite(C, LOW);
//  digitalWrite(D, LOW);
//  delay(1000);
//
////  pinMode(B, OUTPUT);
////  pinMode(C, OUTPUT);
////  pinMode(D, INPUT_PULLUP);
//  DDRB = B011000;
//
//  digitalWrite(B, LOW);
//  digitalWrite(C, HIGH);
//  digitalWrite(D, LOW);
//  delay(1000);
//  

}
