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
  if(btnmode_shpress){
    lcd.setCursor(19,i);
    lcd.print(" ");
    i += 1;
    if (i>3){ 
      i=0;
    }
    lcd.setCursor(19,i);
    lcd.print("-");
    btnmode_shpress = false;
    }
    // // kalau alarm nyala
    // if (alarm_on){
    //   lcd.setCursor(15,2);
    //   lcd.print("SHUT");
    // }
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
  
  Serial.print("atur");

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

