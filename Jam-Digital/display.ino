void jam_display() {
  printNumber((jam/10)%10, 0);
  printNumber(jam%10, 3);
  printNumber(11,6);
  printNumber((menit/10)%10,7);
  printNumber(menit%10,10);
  lcd.setCursor(0,2);
  lcd.print(":");
  lcd.print((detik/10)%10);
  lcd.print(detik%10);

  lcd.setCursor(13,2);
  lcd.print("STOPWT");
  lcd.setCursor(14, 1);
  lcd.print("ALARM");
  lcd.setCursor(15, 0);
  lcd.print("ATUR");
  lcd.setCursor(0, 3);
  lcd.print("alarm ");
  lcd.print("xx : xx");
  lcd.setCursor(15,3);
  lcd.print("SHUT");
  if(btnmode_shpress){
    Serial.print("short");
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
}

void alarm_display(){
  printNumber((jam_alr/10)%10, 0);
  printNumber(jam_alr%10, 3);
  printNumber(11,6);
  printNumber((menit_alr/10)%10,7);
  printNumber(menit_alr%10,10);
  lcd.setCursor(0,2);
  lcd.print(":");
  lcd.print((detik_alr/10)%10);
  lcd.print(detik_alr%10);

    lcd.setCursor(16,0);
    lcd.print("JAM");
    lcd.setCursor(14, 1);
    lcd.print("MENIT");
    lcd.setCursor(16, 2);
    lcd.print("OKE");
    lcd.setCursor(0, 3);
    lcd.print("alarm ");
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
}

void stopwatch_display(){
  printNumber((jam_stw/10)%10, 0);
  printNumber(jam_stw%10, 3);
  printNumber(11,6);
  printNumber((menit_stw/10)%10,7);
  printNumber(menit_stw%10,10);
  lcd.setCursor(0,2);
  lcd.print(":");
  lcd.print((detik_stw/10)%10);
  lcd.print(detik_stw%10);

  lcd.setCursor(14,0);
  lcd.print("START");
  lcd.setCursor(15, 1);
  lcd.print("STOP");
  lcd.setCursor(14, 2);
  lcd.print("RESET");
  lcd.setCursor(16, 3);
  lcd.print("JAM");
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
}

void atur_display(){
  printNumber((jam/10)%10, 0);
  printNumber(jam%10, 3);
  printNumber(11,6);
  printNumber((menit/10)%10,7);
  printNumber(menit%10,10);
  lcd.setCursor(0,2);
  lcd.print(":");
  lcd.print((detik/10)%10);
  lcd.print(detik%10);

  lcd.setCursor(16,0);
  lcd.print("JAM");
  lcd.setCursor(14, 1);
  lcd.print("MENIT");
  lcd.setCursor(16, 2);
  lcd.print("OKE");
  lcd.setCursor(0, 3);
  lcd.print("alarm ");
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
}

