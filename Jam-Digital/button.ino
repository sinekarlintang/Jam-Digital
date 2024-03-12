// button buat mode (fungsi ini ketrigger kalau long press)
void mode_selection(void* param){
  while(btnmode_lgpress){

    if(awal_screen){
      if (i == 0){
        atur_screen = true;
        awal_screen = false;
        alarm_screen = false;
        stopwatch_screen = false;

        btnmode_lgpress = false;

      } else if (i == 1){
        alarm_screen = true;
        awal_screen = false;
        atur_screen = false;
        stopwatch_screen = false;

        btnmode_lgpress = false;
        
      } else if ( i == 2){
        stopwatch_screen = true;
        awal_screen = false;
        alarm_screen = false;
        atur_screen = false;

        btnmode_lgpress = false;
        
      } else if(i==3){
        // matiin alarm kalau bunyi

        btnmode_lgpress = false;
        
      }
    }

    else if (alarm_screen){

    }

    else if (stopwatch_screen){


  
    }

    else if (atur_screen){

    }
  }
}

// button buat tampilan pilih mode (fungsi ini ketrigger kalau short press)
 /* ini untuk tampilan saja, kasi penanda mau pilih menu yang mana
       ATUR - 
      ALARM
  STOPWATCH
       SHUT

   *short press*

       ATUR  
      ALARM -
  STOPWATCH
       SHUT

  */
void modeselect_display(void* param){
  while(btnmode_shpress){
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

// fungsi ini terus dijalankan untuk ngecek apakah ada button mode short press atau long press
void button_detect(void* param){
  while(1){
  buttonState = digitalRead(btnmode);
  // Check if button state has changed
  if (buttonState != lastButtonState) {
    // Button state changed
    if (buttonState == HIGH) {
      // Button is pressed
      buttonPressTime = millis(); // Record the time button was pressed
    } else {
      // Button is released
      if (millis() - buttonPressTime < longPressDuration) {
        // Short press detected
        btnmode_shpress = true;
        Serial.println("short");
      } else {
        // Long press detected
        btnmode_lgpress = true; Serial.println("long");
      }
    }
    delay(50); // Debounce delay 
  }
  lastButtonState = buttonState; // Update last button state
  }
}

// button buat plus minus atur jam/alarm
// ...
