// button buat mode (fungsi ini ketrigger kalau long press)
void mode_selection(void* param){
  while (1) {
    if (xSemaphoreTake(btnmodeSemaphore, portMAX_DELAY) == pdTRUE) {
        if (btnmode_lgpress) {
          if(awal_screen){
            if (i == 0){
              taskENTER_CRITICAL();
              atur_screen = true;
              awal_screen = false;
              alarm_screen = false;
              stopwatch_screen = false;
              btnmode_lgpress = false;
              taskEXIT_CRITICAL();

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
          btnmode_lgpress = false;
        }

        xSemaphoreGive(btnmodeSemaphore);
    }
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
        } else {
          // Long press detected, send semaphore
          if (xSemaphoreTake(btnmodeSemaphore, portMAX_DELAY) == pdTRUE) {
              // Access and modify btnmode_lgpress safely
              btnmode_lgpress = true; 
              Serial.print(btnmode_lgpress);

              // Release the semaphore
              xSemaphoreGive(btnmodeSemaphore);
          }
        }
      }
      delay(50); // Debounce delay 
    }
    lastButtonState = buttonState; // Update last button state
  }
}

// button buat plus minus atur jam/alarm
// ...
