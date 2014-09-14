
#ifndef GingButton_h
#define GingButton_h

// #define DEBUG

#define NULL 0

#define GING_BUTTON_LOW_HIGH 0
#define GING_BUTTON_HIGH_LOW 1

class GingButton {
  int _pin;
  int _buttonTriggerMode;
  int _lastButtonValue;
  long _lastCallbackMillis;
  void (*_callback[2])();
  public:
    GingButton(int pin);
    void setCallback(void (*callback)(), int buttonTriggerMode);
    void loop();
  private:
    void callCallback(int buttonTriggerMode);
};

#endif
