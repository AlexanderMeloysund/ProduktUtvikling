int in1 = 12;
void setup() {
  pinMode(in1, OUTPUT);
  digitalWrite(in1, HIGH);
}
void loop() {
  digitalWrite(in1, LOW);
  delay(250);
  digitalWrite(in1, HIGH);
  delay(250);
}
