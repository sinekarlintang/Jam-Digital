
// button buat menu (fungsi ini ketrigger kalau long press)
void mode_selection(){
  if (btnmode_lgpress) {
    if(awal_screen){
      if (i == 0){                //
        lcd.clear();
        atur_screen = true;
        awal_screen = false;
        alarm_screen = false;
        stopwatch_screen = false;
        btnmode_lgpress = false;

      } else if (i == 1){
        lcd.clear();
        alarm_screen = true;
        awal_screen = false;
        atur_screen = false;
        stopwatch_screen = false;
        btnmode_lgpress = false;
        
      } else if ( i == 2){
        lcd.clear();
        stopwatch_screen = true;
        awal_screen = false;
        alarm_screen = false;
        atur_screen = false;
        btnmode_lgpress = false;
        
      } else if(i==3){
        if (alarm_on){
          alarm_on = false;
        }
        btnmode_lgpress = false;
      }
    }

    else if (alarm_screen){
      if (i == 0){
        if (state_plus == HIGH){
          jam_alr += 1;
        }
        else if (state_min == ){
          jam_alr -= 1;
        }
      }  
    }
    else if (i == 1){
        if (state_plus == HIGH){
          menit_alr += 1;
        }
        else if (state_min == HIGH){
          menit_alr -= 1;
        }
      }  
  
      } else if ( i == 2){
        lcd.clear();
        awal_screen = true;
        atur_screen = false;
        alarm_screen = false;
        stopwatch_screen = false;
        btnmode_lgpress = false;
        
      } else if(i==3){
        btnmode_lgpress = false;
      }      
    }

    else if (stopwatch_screen){
      if (i == 0){
        start = true;
        btnmode_lgpress= false;
      } else if (i == 1){
        start = false;
        btnmode_lgpress= false;
      } else if ( i == 2){
        jam_stw = 0;
        menit_stw = 0;
        detik_stw = 0;
        btnmode_lgpress = false;
      } else if(i==3){
        lcd.clear();
        awal_screen = true;
        atur_screen = false;
        alarm_screen = false;
        stopwatch_screen = false;
        btnmode_lgpress = false;
      }
    }

    else if (atur_screen){
      if (i == 0){
          if (state_plus == HIGH){
            jam += 1;
          }
          else if (state_min == HIGH){
            jam -= 1;
          }

      } else if (i == 1){
          if (state_plus == HIGH){
            menit += 1;
          }
          else if (state_min == HIGH){
            menit -= 1;
          }
        

      } else if ( i == 2){
        lcd.clear();
        awal_screen = true;
        atur_screen = false;
        alarm_screen = false;
        stopwatch_screen = false;
        btnmode_lgpress = false;
        
      } else if(i==3){
        btnmode_lgpress = false;
      }
    }
  }
  }


// fungsi ini terus dijalankan untuk ngecek apakah ada button mode short press atau long press
void button_detect(){

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
      } else {
        // Long press detected
         btnmode_lgpress = true;
      }
    }
    delay(50); // Debounce delay (optional)
  }
  lastButtonState = buttonState; // Update last button state
}
