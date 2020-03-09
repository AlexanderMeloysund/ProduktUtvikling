
// DECLARATION
#include <Servo.h>
int posX = A0;
int posY = A1;
int buttonPin = 2;
int ledPin1 = 7;
int ledPin2 = 4;
 
int xValue;
int yValue;
int buttonState;
int write2Servo1;
int write2Servo2;
Servo servo1;
Servo servo2;
 
//VARIABLES
int oldButtonState = 1; //not pressed
int highValue = 0;  //set LED to HIGH if 1, LOW if 0
 
void setup() {
     pinMode(posX, INPUT);
    pinMode(posY, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    servo1.attach(9);
    servo2.attach(10);
    Serial.begin(9600);
}
 
void loop() {
    xValue = analogRead(posX);
    yValue = analogRead(posY);
    buttonState = digitalRead(buttonPin); //0 if pressed, 1 else
 
    write2Servo1 = map(xValue, 0, 1023, 0, 180);
    write2Servo2 = map(yValue, 0, 1023, 0, 180);
    servo1.write(write2Servo1);
    servo2.write(write2Servo2);
 
    //TURN ON LED WHILE PRESSING
    if (buttonState == 1) { digitalWrite(ledPin1, LOW); }
    else { digitalWrite(ledPin1, HIGH); }
 
    //TURN ON/OFF OTHER LED BY PRESS-RELEASING
    //Detect change: if previous button value was 0 and current state is 1
    if (oldButtonState == 0 && buttonState == 1) {
            if (highValue == 1) { highValue = 0; }
            else { highValue = 1; }
    }
 
    //Output ledPin2 depending on highValue
    if (highValue == 1) { digitalWrite(ledPin2, HIGH); }
    else { digitalWrite(ledPin2, LOW); }
 
    Serial.print("posX: "); Serial.print(xValue);
    Serial.print("\t");
    Serial.print("posY: "); Serial.println(yValue);
    Serial.print("S1: "); Serial.print(write2Servo1);
    Serial.print("\t\t");
    Serial.print("S2: "); Serial.println(write2Servo2);
    Serial.print("Button: "); Serial.print(buttonState);
    Serial.print("\n\n");
 
    oldButtonState = buttonState;
    delay(75); //some delay between reads may be necessary
}
