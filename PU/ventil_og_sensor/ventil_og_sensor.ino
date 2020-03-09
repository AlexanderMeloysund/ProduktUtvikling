#include "TM1637.h"

volatile int NbTopsFan; //measuring the rising edges of the signal
int Calc;
int hallsensor = 2;    //The pin location of the sensor

const int CLK = 7;
const int DIO = 8;
TM1637 tm1637(CLK, DIO);

const int solenoid = 12;

const int flowSensorDelay = 1000;
const int numSolenoidPerSensorRead = 2;
const int solenoidDelay = flowSensorDelay/numSolenoidPerSensorRead;

boolean solenoidStatus = true;
int count = 0;

int timeSensor = millis();
int timeSolenoid = millis();

void rpm ()     //This is the function that the interupt calls
{
  NbTopsFan++;  //This function measures the rising and falling edge of the hall effect sensors signal
  //Serial.println(digitalRead(hallsensor));
}
// The setup() method runs once, when the sketch starts
void setup() //
{
  pinMode(solenoid, OUTPUT);
  digitalWrite(solenoid, HIGH);
  
  pinMode(hallsensor, INPUT); //initializes digital pin 2 as an input
  Serial.begin(9600); //This is the setup function where the serial port is initialised,
  attachInterrupt(digitalPinToInterrupt(2), rpm, RISING); //and the interrupt is attached

  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
}

void loop ()
{
  int timeSolenoid = millis();
  solenoidStatus = !solenoidStatus;
  if (solenoidStatus) {
    digitalWrite(solenoid, HIGH);
  }
  else {
    digitalWrite(solenoid, LOW);
  }
  delay(solenoidDelay);
  count++;
  //Serial.print("SolenoidTime: ");
  //Serial.println(millis()-timeSolenoid);

  if (count >= numSolenoidPerSensorRead) {
    count = 0;
    //Serial.print("SensorTime: ");
    //Serial.println(millis()-timeSensor);
    timeSensor = millis();
    
    cli();      //Disable interrupts
    Calc = (NbTopsFan / 5); //(Pulse frequency x 60) / 5.5Q, = flow rate in L/hour
    Serial.print (Calc, DEC); //Prints the number calculated above
    Serial.print (" L/min\r\n"); //Prints "L/hour" and returns a  new line
    tm1637.displayNum(Calc);
    //Serial.println(digitalRead(hallsensor));
    NbTopsFan = 0;   //Set NbTops to 0 ready for calculations
    sei();      //Enables interrupts
  }
}

