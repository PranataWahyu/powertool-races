void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(9, INPUT);
  Serial.print("Starting up\n");
}

void loop() {
  // put your main code here, to run repeatedly:

  int state = digitalRead(9);
  Serial.print(state == HIGH ? "high\n" : "low\n");
  delay(100);
}
