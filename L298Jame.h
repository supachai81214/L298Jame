#ifndef L298Jame_H
#define L298Jame_H

#include <Arduino.h>

class L298Jame {
  public:
    // Constructor
    L298Jame(int pin_in1fan1, int pin_in2fan1, int pin_enfan1,
             int pin_in3fan2, int pin_in4fan2, int pin_enfan2);

    // Set motor speed
    void setPWM(int fan, int speed);

    // Set motor speed with frequency control
    void setPWM(int fan, int speed, int frequency = 1000);  // Default frequency 1000Hz

    // Enable super fast PWM for high-frequency control
    void setSuperFastPWM(bool enable, int frequency);

  private:
    int in1fan1, in2fan1, enfan1;
    int in3fan2, in4fan2, enfan2;

    void controlFan1(int speed);
    void controlFan2(int speed);
};

#endif
