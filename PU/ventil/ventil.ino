int in1 = 12;
void setup() {
  pinMode(in1, OUTPUT);
}
void loop() {
  // 120 bpm
  digitalWrite(in1, HIGH); // the solenoid closes
  delay(250);
  digitalWrite(in1, LOW); // the solenoid opens
  delay(250);
}
