// Include the Arduino Stepper.h library:
#include <Stepper.h>

// Define number of steps per rotation:
const int stepperPocetKroku = 518;
const int stepperSpeed = 20;
const int stepperDelay = 200;
int stepperPozice = 0;

const int spoustPin = 12;
const int spoustDelka = 200;
const int spoustDelay = 50;

const int buttonPin = 3;
int buttonState = 0;

int bezici = 0;



// Wiring:
// Pin 8 to IN1 on the ULN2003 driver
// Pin 9 to IN2 on the ULN2003 driver
// Pin 10 to IN3 on the ULN2003 driver
// Pin 11 to IN4 on the ULN2003 driver

// Create stepper object called 'myStepper', note the pin order:
Stepper myStepper = Stepper(stepperPocetKroku, 8, 10, 9, 11);

void Spoust() {
  digitalWrite(spoustPin,HIGH);
  delay(spoustDelka);
  digitalWrite(spoustPin,LOW);
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
}

void Reset(){
  myStepper.step(-stepperPozice);
  stepperPozice = 0;
}

void setup() {
  myStepper.setSpeed(stepperSpeed);
  pinMode(buttonPin, INPUT);
  pinMode(spoustPin,OUTPUT);

  Serial.begin(9600);
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
      delay(1000);
      Reset();
    }
    
  } 
  
  if(bezici == 1){
      Beh();
  }
} 

