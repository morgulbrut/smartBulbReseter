
// GE lamps

void ON(int secs) {
  digitalWrite(REL2_PIN, LOW);
  Serial.print("ON for ");
  Serial.print(secs);
  Serial.println(" secs");
  delay(secs * 1000);
}

void OFF(int secs) {
  digitalWrite(REL2_PIN, HIGH);
  Serial.print("OFF for ");
  Serial.print(secs);
  Serial.println(" secs");
  delay(secs * 1000);
}

void resetGEpre27() {
  ON(4);
  OFF(5);
  ON(8);
  OFF(2);
  ON(2);
  OFF(2);
  ON(2);
  OFF(2);
  ON(2);
  OFF(2);
  ON(8);
  OFF(2);
  ON(8);
  OFF(2);
  ON(20);
  OFF(0);
}

void resetGEpost28() {
  ON(4);
  OFF(5);
  for (int i = 0; i <= 5; i++) {
    ON(8);
    OFF(2);
  }
  ON(20);
  OFF(0);
}
