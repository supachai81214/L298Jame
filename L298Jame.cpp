#include "L298Jame.h"

// Constructor
L298Jame::L298Jame(int pin_in1fan1, int pin_in2fan1, int pin_enfan1,
                   int pin_in3fan2, int pin_in4fan2, int pin_enfan2) {
    in1fan1 = pin_in1fan1;
    in2fan1 = pin_in2fan1;
    enfan1 = pin_enfan1;
    in3fan2 = pin_in3fan2;
    in4fan2 = pin_in4fan2;
    enfan2 = pin_enfan2;

    pinMode(in1fan1, OUTPUT);
    pinMode(in2fan1, OUTPUT);
    pinMode(enfan1, OUTPUT);
    pinMode(in3fan2, OUTPUT);
    pinMode(in4fan2, OUTPUT);
    pinMode(enfan2, OUTPUT);
}

// Control Fan 1
void L298Jame::controlFan1(int speed) {
    if (speed > 0) {
        digitalWrite(in1fan1, HIGH);
        digitalWrite(in2fan1, LOW);
        analogWrite(enfan1, speed);  // Forward direction
    } else if (speed < 0) {
        digitalWrite(in1fan1, LOW);
        digitalWrite(in2fan1, HIGH);
        analogWrite(enfan1, -speed); // Reverse direction (absolute value)
    } else {
        digitalWrite(in1fan1, LOW);
        digitalWrite(in2fan1, LOW);
        analogWrite(enfan1, 0);      // Stop
    }
}

void L298Jame::controlFan2(int speed) {
    if (speed > 0) {
        digitalWrite(in3fan2, HIGH);
        digitalWrite(in4fan2, LOW);
        analogWrite(enfan2, speed);  // Forward direction
    } else if (speed < 0) {
        digitalWrite(in3fan2, LOW);
        digitalWrite(in4fan2, HIGH);
        analogWrite(enfan2, -speed); // Reverse direction (absolute value)
    } else {
        digitalWrite(in3fan2, LOW);
        digitalWrite(in4fan2, LOW);
        analogWrite(enfan2, 0);      // Stop
    }
}

// Set PWM for a specific fan
void L298Jame::setPWM(int fan, int speed) {
    if (fan == 1) {
        controlFan1(speed);
    } else if (fan == 2) {
        controlFan2(speed);
    }
}

// Enable Super Fast PWM (using Timer1 for pins 9 and 10)
void L298Jame::setSuperFastPWM(bool enable) {
    if (enable) {
        // Configure Timer1 for Fast PWM mode with no prescaler
        TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1A1) | (1 << COM1B1);
        TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10); // Prescaler = 1 (31.25 kHz)
        ICR1 = 255; // Set top value for 8-bit resolution
    } else {
        // Reset Timer1 to default configuration
        TCCR1A = 0;
        TCCR1B = 0;
    }
}