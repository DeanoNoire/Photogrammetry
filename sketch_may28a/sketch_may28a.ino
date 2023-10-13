// Include the Arduino Stepper.h library:
#include <Stepper.h>

int bezici = 1;
// Define number of steps per rotation:
const int stepperTalirPocetKroku = 44;
const int stepperTalirCelaOtocka = 2024;
const int stepperTalirSpeed = 50;
const int stepperTalirDelay = 1000;
int stepperTalirPozice = 0;

const int stepperZebrikPocetKroku = 44;
const int stepperZebrikCelaOtocka = 2024;
const int stepperZebrikSpeed = 50;
const int stepperZebrikDelay = 1000;
int stepperZebrikPozice = 0;

const int spoustPin = 12;
const int spoustDelka = 600;
const int spoustDelay = 4000;

const int pocetPater = 3;

const int endstopPin = 2;



// Wiring:
// talir
// Pin 8 to IN1 on the ULN2003 driver
// Pin 9 to IN2 on the ULN2003 driver
// Pin 10 to IN3 on the ULN2003 driver
// Pin 11 to IN4 on the ULN2003 driver

// Pin 4 to IN1 on the ULN2003 driver
// Pin 5 to IN2 on the ULN2003 driver
// Pin 6 to IN3 on the ULN2003 driver
// Pin 7 to IN4 on the ULN2003 driver


// Create stepper object called 'myStepper', note the pin order:
Stepper stepperTalir = Stepper(stepperTalirPocetKroku, 8, 10, 9, 11);
Stepper stepperZebrik = Stepper(stepperZebrikPocetKroku, 4, 6, 5, 7);

void Spoust() {
  digitalWrite(spoustPin,LOW);
  delay(spoustDelka);
  digitalWrite(spoustPin,HIGH);
  delay(spoustDelay);
}

void Otocka(){
  stepperTalir.step(stepperTalirPocetKroku);
  steppertalirPozice = stepperTalirPozice + stepperTalirPocetKroku;
  delay(stepperTalirDelay);
}

void Beh(){
    Serial.println(stepperTalirPozice);
    Otocka();  
    Spoust();
    Levelcheck();
}

void Levelcheck(){
  if(stepperTalirPozice == stepperTalirCelaOtocka){
       stepperTalirPozice = 0;
       Levelup();
  }
}

void Homing(){
  int endStopState;
  do {
    endStopState = digitalRead(endstopPin);
    if(endStopState == LOW){
      stepper.setSpeed(0);
      bezici = 0;
    } else {
       stepperZebrik.step(-1);
    }
  } while (endstopState != LOW);
  
}

void Levelup(){
    if(patro < pocetPater){
      stepperZebrik.step(stepperZebrikPocetKroku);
      patro = patro + 1;  
      delay(stepperZebrikDelay);
    }
    if(patro == pocetPater){
      Homing();
    }
  }




void setup() {
  stepperTalir.setSpeed(stepperTalirSpeed);
  pinMode(spoustPin,OUTPUT);
  pinMode(endstopPin, INPUT_PULLUP);

  digitalWrite(spoustPin,HIGH);
  Serial.begin(9600);

}

void loop() {
  if(bezici == 1) {
    Homing();
    Beh();
  }
  

} 
