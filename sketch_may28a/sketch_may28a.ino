// Include the Arduino Stepper.h library:
#include <Stepper.h>
#include <TM1637.h>

// Define number of steps per rotation:
const int stepperPocetKroku = 44;
const int stepperSpeed = 50;
const int stepperSpeedReset = 100;
const int stepperDelay = 200;
int stepperPozice = 0;

const int spoustPin = 12;
const int spoustDelka = 600;
const int spoustDelay = 50;

const int buttonPin = 3;
int buttonState = 0;

int bezici = 0;

int patro = 0;

const int pocetPater = 0;

const int ClkPin = 7;
const int DioPin = 6;
TM1637 tm(ClkPin,DioPin);



// Wiring:
// Pin 8 to IN1 on the ULN2003 driver
// Pin 9 to IN2 on the ULN2003 driver
// Pin 10 to IN3 on the ULN2003 driver
// Pin 11 to IN4 on the ULN2003 driver

// Create stepper object called 'myStepper', note the pin order:
Stepper myStepper = Stepper(stepperPocetKroku, 8, 10, 9, 11);

void Spoust() {
  digitalWrite(spoustPin,LOW);
  delay(spoustDelka);
  digitalWrite(spoustPin,HIGH);
  delay(spoustDelay);
}

void Otocka(){
  myStepper.step(stepperPocetKroku);
  stepperPozice = stepperPozice + stepperPocetKroku;
  delay(stepperDelay);
}

void Beh(){
    Serial.println(stepperPozice);
    Otocka();  
    Spoust();
    Levelcheck();
}

void Levelcheck(){
  if(stepperPozice == 440){
       stepperPozice = 0;
       Levelup();
  }


}

void Levelup(){
    if(patro < pocetPater){
      patro = patro + 1;  
    }
    if(patro == pocetPater){
    bezici = 0;  
    }
  }



void Reset(){
  myStepper.setSpeed(stepperSpeedReset);
  myStepper.step(-stepperPozice);
  stepperPozice = 0;
  myStepper.setSpeed(stepperSpeed);
}

void displayNumber(int num){
    tm.display(3, num % 10);   
    tm.display(2, num / 10 % 10);   
    tm.display(1, num / 100 % 10);   
    tm.display(0, num / 1000 % 10);
}

void setup() {
  myStepper.setSpeed(stepperSpeed);
  pinMode(buttonPin, INPUT);
  pinMode(spoustPin,OUTPUT);

  digitalWrite(spoustPin,HIGH);
  Serial.begin(9600);

  tm.init();
  tm.set(1);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  
  if (buttonState == HIGH) {
    if (bezici == 0){
      Serial.println("Start");
      bezici = 1;
      delay(1000);
    }
    else {
      Serial.println("Konec");
      bezici = 0;
      displayNumber(0000);
      delay(1000);
      Reset();
    }
    
  } 
  
  if(bezici == 1){
      Beh();
      displayNumber(patro*1000 + (stepperPozice)/22);
  }
} 
