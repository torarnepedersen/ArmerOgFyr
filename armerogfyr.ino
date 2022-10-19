/* Armèr og fyr. 
 * Knapp tilkoblet pin 2 armerer en enhet. Denne blir desarmert etter 1 minutt.
 * Knapp tilkoblet pin 3 fyrer et rele.
 * LED tilkoblet pin 4 blinker så lenge enheten ikke er armert, lyser da den er armert
 */
#define ArmerPIN 2
#define FyrPIN 3
#define LEDPIN 4
#define RelePIN 5
unsigned long TidsTeller=0;
unsigned long ArmertTid=0;
bool LEDstatus=LOW;
bool Armert=false;
/*
 * Variablene nedenfor endrer oppførsel til programmet og må justeres etter hvordan det skal se ut
 * og hvordan reaksjonstid man har på knapper/rele/mynt etc.
 */
unsigned long BlinkeFrekvens=500; //lavere tall gir raskere blinking (millisekund)
int KnappeTrykkForsinkelse=100; //Denne forsinkelsen er for at et knappetrykk ikke skal registreres flere ganger på rad
unsigned long HoldEnhetArmert=60000; //Hvor lenge skal enheten være armert før den automatisk desarmeres ved inaktivitet (millisekunder)
int FyrAv=200; //Hvor mange millisekund releet som fyrer av skal stå på før det skrus av igjen

void setup() {
  pinMode(ArmerPIN, INPUT);
  pinMode(FyrPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(RelePIN, OUTPUT);
  TidsTeller=millis();
  ArmertTid=millis();
}
void Fyr() {
      digitalWrite(RelePIN, HIGH);
      delay(FyrAv);             //Hvor mange millisekund releet skal stå på før det skrus av igjen
      digitalWrite(RelePIN, LOW);
}
void Armer(){
  ArmertTid=millis();
  Armert=true;
  LEDstatus=HIGH;
  digitalWrite(LEDPIN, LEDstatus);
  delay(KnappeTrykkForsinkelse);     //Denne forsinkelsen er for at et knappetrykk ikke skal registreres flere ganger på rad
  while (ArmertTid+HoldEnhetArmert>millis()) { //Hold enheten armèrt x millisekunder.
    if (digitalRead(ArmerPIN)==HIGH) { //Hvis man kjører Knapp1 (Armer) igjen skal enheten desarmeres
      Armert=false;
      delay(KnappeTrykkForsinkelse);  //Denne forsinkelsen er for at et knappetrykk ikke skal registreres flere ganger på rad
      return;
  }
    if (digitalRead(FyrPIN)==HIGH) {  //Knapp2/Fyr slår inn.
      Fyr();
      Armert=false;                   //Skal desarmeres etter det er fyrt av
      return;
      }
  }
  Armert=false;                      //Tiden HoldEnhetArmert har gått ut. Desarmeres autoamtisk.
}

void Blink(){
  LEDstatus=!LEDstatus;
  digitalWrite(LEDPIN, LEDstatus);
}
void loop() {
  if (digitalRead(ArmerPIN)==HIGH) { //Knapp1/Armer er aktivert
    Armer();
  }
  if (TidsTeller+BlinkeFrekvens<millis()) {
    Blink();
    TidsTeller=millis();
  }
}
