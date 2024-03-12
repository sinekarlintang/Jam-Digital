#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <FreeRTOS.h> // aku coba gapake freertos display lcdnya telat responnya
#include <task.h>
#include <queue.h>
#include <semphr.h>

// library yang perlu didonlot : FreeRTOS by Richard Barry dan LiquidCrystal I2C by Frank de Brabander

LiquidCrystal_I2C lcd(0x27, 20, 4); // Set the LCD address to 0x27 by Teach Me Something
int jam, menit, detik, i;

int buttonState = 0;        // current state of the button
int lastButtonState = 0;    // previous state of the button
int longPressDuration = 500; // millis
unsigned long buttonPressTime = 0; // time when button was pressed
bool btnmode_shpress, btnmode_lgpress, btnplus_press, btnmin_press, alarm_on;
//     short press       long press           
volatile bool awal_screen, atur_screen, alarm_screen, stopwatch_screen;

// Define semaphore
SemaphoreHandle_t btnmodeSemaphore;

// Initialize semaphore


// ini untuk library lcd
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

// arduino yang aku punya hanya ada arduino due yang pakainya ARM bukan AVR, karena nama registernya beda
// dan pinnya beda jadi kasi kondisional untuk ngecek apakah core yang dipake AVR atau ARM (abaikan saja bagian ini)

#ifdef __arm__ // Check if compiling for ARM (e.g., Arduino Due)

const int btnmode = 4;
#include <sam.h>
void arm_timer_function() {
  pmc_set_writeprotect(false); // Disable write protection for PMC (Power Management Controller)
  pmc_enable_periph_clk(ID_TC0); // Enable peripheral clock for Timer Counter 0
  
  // Configure Timer Counter 0 (TC0) for a 1 Hz frequency
  TC_Configure(TC0, 0, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
  TC_SetRC(TC0, 0, 656249); // = 84000000 / (128 * 1) - 1 (must be <65536)
  TC_Start(TC0, 0); // Start the timer
  
  // Enable Timer Counter 0 (TC0) interrupt on RC compare
  TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;
  TC0->TC_CHANNEL[0].TC_IDR = ~TC_IER_CPCS; // Disable all other interrupts for TC0
  NVIC_EnableIRQ(TC0_IRQn); // Enable TC0 interrupt vector
}
void TC0_Handler() {
  detik += 1;
  if (detik >59){ 
    detik = 0;
    menit += 1;
    if (menit > 59){
      menit =0;
      jam +=1 ;
      if (jam> 23){
        jam =0;
      }
    }
  }

  TC_GetStatus(TC0, 0); // Reset TC0 interrupt flag
}


#else // AVR (Arduino Nano)
#include <avr/io.h>
void avr_timer_function() {
  cli(); // stop interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 1 Hz increments
  OCR1A = 62499; // = 16000000 / (256 * 1) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 256 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts
}
ISR(TIMER1_COMPA_vect){
  detik += 1;
  if (detik >59){ 
    detik = 0;
    menit += 1;
    if (menit > 59){
      menit =0;
      jam +=1 ;
      if (jam> 23){
        jam =0;
      }
    }
  }
  TIFR1 |= (1 << OCF1A);  // reset flag
}
#endif



void setup() {
  // debugging purpose
  Serial.begin(115200);

  // cek apakah mau menjalankan timer untuk AVR atau ARM (ini hanya ada karena aku gapunya arduino yang pake AVR (nano, uno atau lainnya))
  #ifdef __arm__
    arm_timer_function();
    pinMode(btnmode,INPUT); // ini aku coba coba di arduino due pakenya 4
  #else
    avr_timer_function();
  #endif

  // inisiasi lcd
  lcdinit();

  lcd.setCursor(19,i);
  lcd.print("-");
  awal_screen = true;
  i =0;
  btnmodeSemaphore = xSemaphoreCreateMutex();
  //task display prioritasnya harus paling tinggi (untuk sekarang pilih 2) biar ga kepotong task lain
  //kalau ada task yg ga jalan bisa jadi karena prioritasnya, coba coba ganti
  xTaskCreate(atur_display, "ATUR", 128, NULL, 0, NULL);
  // xTaskCreate(alarm_display, "ALARM", 128, NULL, 1, NULL);
  // xTaskCreate(stopwatch_display, "STOPWATCH", 128, NULL, 1, NULL);
  xTaskCreate(jam_display, "JAM", 128, NULL, 1, NULL);


  xTaskCreate(mode_selection, "MODE", 128, NULL, 1, NULL);
  xTaskCreate(button_detect, "BUTTON", 128, NULL, 1, NULL);
  vTaskStartScheduler();

}

void loop() {

}
