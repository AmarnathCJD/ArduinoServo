#include <Servo.h>

const int trigPin = 5;
const int echoPin = 6;

long duration;
int distance;
Servo myServo;

int open = 0;
int op_complete = 1;

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);
    myServo.attach(7);
    // resetServo();
}

void resetServo() {
    for (int pos = myServo.read(); pos >= 0; pos -= 1) {
        myServo.write(pos);
        delay(15);
    }
    open = 0;
    op_complete = 1;
}

void loop() {
    distance = calculateDistance();
    Serial.print("DIST: ");
    Serial.println(distance);

    if (distance < 15 && distance != 0 && op_complete == 1) {
        if (open == 0) {
            Serial.println("OPEN: close");
            for (int pos = 0; pos <= 180; pos += 1) {
                myServo.write(pos);
                op_complete = 0;
                delay(15);
            }
            open = 1;
            op_complete = 1;
            delay(1000);
        }
    } else if (distance > 100 && op_complete == 1) {
        if (open == 1) {
            Serial.println("OPEN: yes");
            for (int pos = 180; pos >= 0; pos -= 1) {
                myServo.write(pos);
                delay(15);
            }
            open = 0;
            op_complete = 1;
            delay(1000);
        }
    }
}

int calculateDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    return distance;
}
