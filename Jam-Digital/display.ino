void jam_display(void* param) {
  while(awal_screen){
  printNumber((menit/10)%10, 0);
  printNumber(menit%10, 3);
  printNumber(11,6);
  printNumber((detik/10)%10,7);
  printNumber(detik%10,10);

  lcd.setCursor(13,2);
  lcd.print("STOPWT");
  lcd.setCursor(14, 1);
  lcd.print("ALARM");
  lcd.setCursor(15, 0);
  lcd.print("ATUR");
  lcd.setCursor(0, 3);
  lcd.print("Alarm ");
  lcd.print("xx : xx");
  }
}

void alarm_display(void* param){
  while(alarm_screen){
  lcd.print("Alarm");

    lcd.setCursor(16,0);
    lcd.print("JAM");
    lcd.setCursor(14, 1);
    lcd.print("MENIT");
    lcd.setCursor(16, 2);
    lcd.print("OKE");
    lcd.setCursor(0, 3);
    lcd.print("Alarm ");
    lcd.print("xx : xx");
  }
}

void stopwatch_display(void* param){
  while(stopwatch_screen){

  lcd.print("stopwatch");
  }

}

void atur_display(void* param){
  while(atur_screen){
lcd.print("atur");

  lcd.setCursor(16,0);
  lcd.print("JAM");
  lcd.setCursor(14, 1);
  lcd.print("MENIT");
  lcd.setCursor(16, 2);
  lcd.print("OKE");
  lcd.setCursor(0, 3);
  lcd.print("Alarm ");
  
  lcd.print("xx : xx");
  }

}

