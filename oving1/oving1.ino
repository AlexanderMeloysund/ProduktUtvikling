int LED = 5;
int brightness = 0;

void setup() {
  pinMode(LED, OUTPUT);
  analogWrite(LED, brightness);
  Serial.begin(9600);
}

void loop() {
  while (brightness < 255) {
    analogWrite(LED, brightness);
    delay(1000);
    Serial.println(brightness);
    brightness = brightness+20;
  }
  brightness = 0;
}
