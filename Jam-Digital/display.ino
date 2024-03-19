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
  lcd.print((jam_alr/10)%10);
  lcd.print(jam_alr%10);
  lcd.print(":");
  lcd.print((menit_alr/10)%10);
  lcd.print(menit_alr%10);

  lcd.setCursor(15,3);
  lcd.print("SHUT");
  if(btnmode_shpress){
    // Serial.print("short");
    
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
  lcd.print((jam_alr/10)%10);
  lcd.print(jam_alr%10);
  lcd.print(":");
  lcd.print((menit_alr/10)%10);
  lcd.print(menit_alr%10);

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
  if (i == 0){
    if (state_plus == HIGH){
      // Serial.print("plus");
      jam_alr += 1;
      if(jam_alr >23){jam_alr=0;}
    }
    else if (state_min == HIGH){
      jam_alr -= 1;
      
      if(jam_alr <0){jam_alr=23;}
    }

} else if (i == 1){
    if (state_plus == HIGH){
      menit_alr += 1;
            if(menit_alr >59){menit_alr=0;}
    }
    else if (state_min == HIGH){
      menit_alr -= 1;
            if(menit_alr <0){menit_alr=59;}
    }
  

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
  lcd.print((jam_alr/10)%10);
  lcd.print(jam_alr%10);
  lcd.print(":");
  lcd.print((menit_alr/10)%10);
  lcd.print(menit_alr%10);

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
  if (i == 0){
    if (state_plus == HIGH){
      // Serial.print("plus");
      jam += 1;
      if(jam >23){jam=0;}
    }
    else if (state_min == HIGH){
      jam -= 1;
      if(jam <0){jam=23;}
    }

} else if (i == 1){
    if (state_plus == HIGH){
      menit += 1;
      if(menit >59){menit=0;}
    }
    else if (state_min == HIGH){
      menit -= 1;
      
      if(menit <0){menit=59;}
    }
        

  }
}

