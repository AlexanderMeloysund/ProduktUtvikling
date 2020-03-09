// DECLARATION
int potPin = A0;  //Signal from A0 will be called as potPin
int PWM = 5;  // Port 5 will be named as PWM
int potValue;  // Variable for a read value
int writeValue; // Variable that will be used to write value to the PWM port
 
void setup() {
   pinMode(potPin, INPUT);  //set potPin to be an input
   pinMode(PWM, OUTPUT); //set PWM to be an OUTPUT
   Serial.begin(9600);    // turn on Serial Port
}
 
void loop() {
   potValue = analogRead(potPin);//Read the voltage on the Potentiometer
   writeValue = map(potValue, 0, 1023, 0, 255);
   analogWrite(PWM, writeValue); //Write writeValue to the PWM
   Serial.print("Potentiometer value: ");//For debugging print your values
   Serial.print(potValue);
   Serial.print("\t");  //Just a couple of spaces
   Serial.print("PWM value: ");
   Serial.println(writeValue); //println also makes a new line afterwards
}
