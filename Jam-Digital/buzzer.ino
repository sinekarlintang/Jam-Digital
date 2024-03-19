void loop() {
  if (alarm_on == true) {
    tone(buzzer, 1000);
    delay(10000);
  }
}

void alarm_int() {
  alarm_on = !alarm_on;
}
