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

// Control Fan 2
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

// Set PWM for a specific fan with optional frequency control
void L298Jame::setPWM(int fan, int speed, int frequency) {
    if (frequency > 1000) {  // ใช้ความถี่สูงกว่า 1000Hz จะเข้าโหมด fast PWM
        setSuperFastPWM(true, frequency);  // เปิดการควบคุมความถี่ที่เราป้อน
    } else {
        setSuperFastPWM(false, frequency); // ถ้าความถี่ต่ำกว่า 1000Hz ใช้ PWM ปกติ
    }

    // ตรวจสอบทิศทางการหมุนและปรับการควบคุมให้เหมาะสม
    if (fan == 1) {
        controlFan1(speed);
    } else if (fan == 2) {
        controlFan2(speed);
    }
}

void L298Jame::setSuperFastPWM(bool enable, int frequency) {
    if (enable) {
        // คำนวณค่า ICR1 ตามความถี่ที่ผู้ใช้ระบุ
        long timerFreq = 16000000;  // ความถี่ของระบบ (16MHz)
        long prescaler = 1;  // ใช้ prescaler = 1 เพื่อให้ความถี่สูงสุด
        ICR1 = timerFreq / prescaler / frequency - 1;  // คำนวณค่า ICR1 ตามความถี่
        TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1A1) | (1 << COM1B1); 
        TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10);  // ตั้งค่า Timer1 ให้ทำงานที่ความถี่ที่กำหนด
    } else {
        // รีเซ็ต Timer1 กลับสู่การตั้งค่าปกติ
        TCCR1A = 0;
        TCCR1B = 0;
    }
}
