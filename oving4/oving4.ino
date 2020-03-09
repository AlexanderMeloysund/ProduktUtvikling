
//EXERCISE 4 - ARDUINO B - DUAL MODE
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = { "00097", "00098" };
 
int posX = A0;                                                    //Hor. joystick movement to port A0
int posY = A1;                                                    //Ver. joystick movement to port A1
int ledPinB = 3;                                                  //LED-diode connected to port 3
int buttonPin = 2;                                                //Button of joystick connected to port 2
int xValue;                                                     //Hor. joystick raw value
int yValue;                                                       //Ver. joystick raw value
int write2Servo1;                                                 //Value b/w 0-180 to be transmitted to Servo1 in A
int write2Servo2;                                                 //Value b/w 0-180 to be transmitted to Servo2 in A
boolean buttonState;
void setup() {
    pinMode(ledPinB, OUTPUT);                                     //Set ledPinB to be an OUTPUT
    pinMode(buttonPin, INPUT_PULLUP);                             //Set button of joystick to be INPUT
    pinMode(posX, INPUT);                                         //Set hor. joystick movements as INPUT
    pinMode(posY, INPUT);                                        //Set ver. joystick movements as INPUT
 
    Serial.begin(9600);
    radio.begin();
    radio.openReadingPipe(1, addresses[1]);                       //00001: Reading Mode
    radio.openWritingPipe(addresses[0]);                          //00002: Transmitting Mode
    radio.setPALevel(RF24_PA_MIN);
}
 
void loop() {
    delay(5);
    radio.startListening();                                       //Receiving mode;
    if (radio.available()) {
            int received_pwmValue = 0;
            radio.read(&received_pwmValue, sizeof(received_pwmValue));
            analogWrite(ledPinB, received_pwmValue);                    //Write received PWM-value to ledPinB-port
            Serial.print("Received PWM value: ");                       //Print received PWM-value for debugging purposes
            Serial.print(received_pwmValue);
    }
 
    delay(50);                                                    //Get bad communication if you choose lower
    radio.stopListening();                                     //Transmitting mode;
    buttonState = digitalRead(buttonPin);                       //0 if pressed, 1 else
    xValue = analogRead(posX);                                  //Read hor. joystick movements
    yValue = analogRead(posY);                                    //Read ver. joystick movements
    write2Servo1 = map(xValue, 0, 1023, 0, 180);
    write2Servo2 = map(yValue, 0, 1023, 0, 180);
    radio.write(&buttonState, sizeof(buttonState));             //Transmit joystick values
    radio.write(&write2Servo1, sizeof(write2Servo1));
    radio.write(&write2Servo2, sizeof(write2Servo2));
    Serial.print("\t\t"); Serial.print("Transmitted joystick values {B, X, Y}: ");
    Serial.print(buttonState); Serial.print("\t");
    Serial.print(write2Servo1); Serial.print("\t");
    Serial.println(write2Servo2);
}
