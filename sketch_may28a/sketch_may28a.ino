// Include the Arduino Stepper.h library:
#include <Stepper.h>
#include <TM1637Display.h>

int homed = 0;
int bezici = 1;
// Define number of steps per rotation:
const int stepperTalirPocetKroku = 44;
const int stepperTalirCelaOtocka = 2024;
const int stepperTalirSpeed = 50;
const int stepperTalirDelay = 300;
int stepperTalirPozice = 0;

float stepperTalirOsmina = stepperTalirCelaOtocka / 8.00;

const int stepperZebrikPocetKroku = 44;
const int stepperZebrikCelaOtocka = 2024;
const int stepperZebrikSpeed = 50;
const int stepperZebrikDelay = 300;
int stepperZebrikPozice = 0;

const int spoustPin = 12;
const int spoustDelka = 600;
const int spoustDelay = 400;

const int displayClk = 14;
const int displayDio = 15;

const int pocetPater = 1;

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

TM1637Display display(displayClk, displayDio);

void Spoust() {
  digitalWrite(spoustPin,LOW);
  delay(spoustDelka);
  digitalWrite(spoustPin,HIGH);
  delay(spoustDelay);
}

void Otocka(){
  stepperTalir.step(stepperTalirPocetKroku);
  stepperTalirPozice = stepperTalirPozice + stepperTalirPocetKroku;
  Serial.println(stepperTalirPozice/stepperTalirOsmina);
  displayShow((stepperTalirPozice/stepperTalirOsmina)+2);
  delay(stepperTalirDelay);
}

void Beh(){
    displayShow(1);
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
  Serial.println("Homing");
  displayShow(0);
  int endStopState;
  do {
    endStopState = digitalRead(endstopPin);
    if(endStopState == LOW){
      } else {
       //stepperZebrik.step(-1);
       stepperTalir.step(-1);
    }
  } while (endStopState != LOW);
    homed = 1;
    Serial.println("Homed");
}

void Levelup(){
    Serial.println("Level up");
    if(stepperZebrikPozice < pocetPater){
      displayShow(0);
      stepperZebrik.step(stepperZebrikPocetKroku);
      stepperZebrikPozice = stepperZebrikPozice + 1;  
      delay(stepperZebrikDelay);
    }
    if(stepperZebrikPozice == pocetPater){
      Serial.println("Konec");
      Homing();
      bezici = 0;
    }
  }

void displayShow(int x){
  byte data[] = {0, 0, 0, 0};
  //display.clear();
  if(x == 0){
      data[3] =  0b01110110;  // Homing
      display.setSegments(data);
    }  

  if(x == 2){
      data[3] =  0b00000110;
      display.setSegments(data);
    }  
  if(x == 3){
      data[3] =  0b00110000;
      display.setSegments(data);
    }  
}




void setup() {
  stepperTalir.setSpeed(stepperTalirSpeed);
  display.setBrightness(7);
  display.clear();
  pinMode(spoustPin,OUTPUT);
  pinMode(endstopPin, INPUT_PULLUP);

  digitalWrite(spoustPin,HIGH);
  Serial.begin(9600);

}

void loop() {
  if(homed == 0){
    Homing();  
  }
  Serial.println("X");
  Serial.println(stepperTalirOsmina);
  if(bezici == 1) {
    Beh();
  }
  

} 
