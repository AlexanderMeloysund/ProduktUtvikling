#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN

const byte addresses[][3] = { "97", "98" };
const int sampleSize = 50;

int ledPin = 10;
int soundSensorA = A0;
int soundSensorD = 3;
int lastNoiseSum = (unsigned int) 1023*sampleSize;
int count = 0;

int clap = 0;
long timeStart = 0;
long lastTime = 0;
boolean statusLights = false;
int noiseSum = 0;

int pwmValue = 0;

const int led[4] = {5,6,9};
int i = 0;
int speed = 1000;
boolean reversed = false;

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
  pinMode(led[2], OUTPUT);
  pinMode(led[3], OUTPUT);
  pinMode(led[4], OUTPUT);
  pinMode(soundSensorA, INPUT);
  pinMode(soundSensorD, INPUT);
  
  radio.begin();
  radio.openReadingPipe(0, addresses[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  int noise = analogRead(soundSensorA);
  noiseSum += noise;
  count++;
  if (count++ >= sampleSize) {
    //Serial.println(noiseSum);
    count = 0;
    if (noiseSum - lastNoiseSum > 20 && millis() - lastTime > 100){
      clap++;

      if (clap == 1) {
        timeStart = millis();
      }
      
      lastTime = millis();
      Serial.println(clap);
    }
    lastNoiseSum = noiseSum;
    noiseSum = 0;

    //Serial.println(millis()-timeStart);
 
    if (clap >= 2) {
      statusLights = !statusLights;
      if (statusLights) {
        analogWrite(ledPin, pwmValue);
      }
      else {
        analogWrite(ledPin, 0);
      }
      clap = 0;
    }
    else if(millis()-timeStart > 700) {
      clap = 0;
    }
  }
  if (radio.available()) {
    radio.read(&pwmValue, sizeof(pwmValue));
    if (statusLights) {
      analogWrite(ledPin, pwmValue);
    }
    //Serial.print("PWM value: ");
    //Serial.println(pwmValue);
  }
  /*
  if (!statusLights) {
    analogWrite(led[i/speed], pwmValue);
  }
  if (i % speed == 0) {
    analogWrite(led[i/speed-1], 0);
  }
  i++;
  if (i > 3*speed) {
    i = 0;
  }*/

  if (!statusLights) {
    analogWrite(led[i/speed], pwmValue);
  }
  if (i % speed == 0) {
    if (reversed) {
      analogWrite(led[i/speed], 0);
    }
    else {
      analogWrite(led[i/speed-1], 0);
    }
  }
  if (reversed) {
    i--;
  }
  else {
    i++;
  }
  if (i > 3*speed || i < 0) {
    reversed = !reversed;
  }
}
