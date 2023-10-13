#include <TM1637Display.h>

#define CLK 14  // Change this to the pin you've connected to CLK
#define DIO 15  // Change this to the pin you've connected to DIO

TM1637Display display(CLK, DIO);

void setup() {
  display.setBrightness(7);

}

void loop() {
  byte data[] = {0, 0, 0, 0};
  data[1] = 0b00001000; // Turn on the middle segment
  display.setSegments(data);
  delay(2000); // Display for 2 seconds
  display.clear();
  delay(1000); // Pause for 1 second

}
