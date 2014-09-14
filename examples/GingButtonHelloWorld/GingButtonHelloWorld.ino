#include <GingButton.h>

GingButton button(3);

void setup() {
  Serial.begin(9600);
  button.setCallback(&helloWorld, GING_BUTTON_LOW_HIGH);
}

void loop() {
  button.loop();
}

void helloWorld() {
  Serial.println("Hello World!");
}
