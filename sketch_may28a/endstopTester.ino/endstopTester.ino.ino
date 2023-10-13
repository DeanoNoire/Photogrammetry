const int endstopPin = 2;
int bezici = 1;

void Homing(){
  int endStopState;
  do {
    endStopState = digitalRead(endstopPin);
    if(endStopState == LOW){
      Serial.println("Triggered!");
      stepper.setSpeed(0);
      bezici = 0;
    } else {
       stepperZebrik.step(-1);
    }
  } while (endstopState != LOW);
  
}
void setup() {
  
  pinMode(endstopPin, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  if(bezici == 1) {
    Homing();
  }
