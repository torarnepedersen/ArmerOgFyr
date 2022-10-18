/* Armèr og fyr. 
 * Knapp tilkoblet pin 2 armerer en enhet. Denne blir dearmert etter 1 minutt.
 * Knapp tilkoblet pin 3 fyrer et rele.
 * LED tilkoblet pin 4 blinker så lenge enheten ikke er armert, lyser da den er armert
 */
#define ArmerPIN 2
#define FyrPIN 3
#define LEDPIN 4
#define RelePIN 5
unsigned long BlinkeFrekvens=500; //lavere tall gir raskere blinking (millisekund)
unsigned long TidsTeller=0;
unsigned long ArmertTid=0;
bool LEDstatus=LOW;
bool Armert=false;
void setup() {
  pinMode(ArmerPIN, INPUT);
  pinMode(FyrPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(RelePIN, OUTPUT);
  TidsTeller=millis();
  ArmertTid=millis();
  Serial.begin(9600);
}
void Armer(){
  ArmertTid=millis();
  LEDstatus=HIGH;
  digitalWrite(LEDPIN, LEDstatus);
  delay(100);
  while (ArmertTid+60000>millis()) { //Hold enheten armèrt x millisekunder.
    if (digitalRead(ArmerPIN)==HIGH) {
      Armert=false;
      delay(100);
      return;
  }
    if (digitalRead(FyrPIN)==HIGH) {
      digitalWrite(RelePIN, HIGH);
      delay(100);
      digitalWrite(RelePIN, LOW);
      Armert=false;
      return;
    }
    
  }
  Armert=false;
}

void Blink(){
  LEDstatus=!LEDstatus;
  digitalWrite(LEDPIN, LEDstatus);
}
void loop() {
  if (digitalRead(ArmerPIN)==HIGH) {
    Armert=!Armert;
  }
  if (Armert==true) {
    Armer();
  }
  if (TidsTeller+BlinkeFrekvens<millis()) {
    Blink();
    TidsTeller=millis();
  }
}
