void loop() {
  if (alarm_on == true) {
    tone(buzzer, 1000);
    delay(10000);
    noTone(buzzer);
    delay(3000);
  }
}

// Interrupt service routine to set the silenceBuzzer variable
void alarm_int() {
  alarm_on = !alarm_on;
}
