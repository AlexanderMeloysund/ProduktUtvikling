#include "TM1637.h"

volatile int NbTopsFan; //measuring the rising edges of the signal
int flowRate;
int flowSensor = 2;

const int CLK = 7;
const int DIO = 8;
TM1637 tm1637(CLK, DIO);

// the flow sensor sends a signal at certain rotations of the internal wheel
// rpm() interrupts and counts each time the flow sensor sends a signal
void rpm ()  
{
  NbTopsFan++; 
}

void setup() //
{
  pinMode(flowSensor, INPUT);
  Serial.begin(9600);
  attachInterrupt(0, rpm, RISING); // Interrupts when the input raises

  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
}

void loop ()
{
  NbTopsFan = 0;   //Set NbTops to 0 ready for calculations
  sei();      //Enables interrupts
  delay (1000);
  cli();      //Disable interrupts
  flowRate = (NbTopsFan / 5); //flow rate in L/hour. The constant 5 is based on experiments
  Serial.print (flowRate, DEC);
  Serial.print (" L/hour\r\n");

  tm1637.displayNum(flowRate); // Displays the flow on the screen
}
