
#include <Arduino.h>
#include "GingButton.h"

#ifdef DEBUG
int _gingButtonDebugPring(const char* message, ...) {
  Serial.println(message);
}
#else
int _gingButtonDebugPring(const char* message, ...) {
}
#endif
int (*gingButtonDebug)(const char*, ...) = &_gingButtonDebugPring;

GingButton::GingButton(int pin) {
  _pin = pin;
  _lastButtonValue = -1;
  _callback[GING_BUTTON_LOW_HIGH] = NULL;
  _callback[GING_BUTTON_HIGH_LOW] = NULL;
  _lastCallbackMillis = 0;
  pinMode(_pin, INPUT);
}
void GingButton::setCallback(void (*callback)(), int buttonTriggerMode) {
  gingButtonDebug("trying to set callback");
  if (buttonTriggerMode != GING_BUTTON_LOW_HIGH
      && buttonTriggerMode != GING_BUTTON_HIGH_LOW) {
    gingButtonDebug("not a valid trigger mode");
    return;
  }
  gingButtonDebug("setting callback");
  _callback[buttonTriggerMode] = callback;
}
void GingButton::loop() {
  if (_lastCallbackMillis > millis() - 500) {
    return;
  }
  if (_lastButtonValue == -1) {
    _lastButtonValue = digitalRead(_pin);
    return;
  }
  int _buttonValue = digitalRead(_pin);
  if (_buttonValue != _lastButtonValue) {
    if (_lastButtonValue == LOW) {
      callCallback(GING_BUTTON_LOW_HIGH);
    } else {
      callCallback(GING_BUTTON_HIGH_LOW);
    }
    _lastButtonValue = _buttonValue;
  }
}
void GingButton::callCallback(int buttonTriggerMode) {
  if (_callback[buttonTriggerMode] == NULL) {
    return;
  }
  _callback[buttonTriggerMode]();
  _lastCallbackMillis = millis();
}
