void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(9, INPUT_PULLUP);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int ret = digitalRead(9);
  Serial.write(ret == HIGH ? "high\n" : "low\n");
  
}
