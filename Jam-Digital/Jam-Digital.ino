#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// inisialisasi pin
const int btnmode = 3;
const int btnmin = 4;
const int btnplus = 5;
const int buzzer = 7;

// library yang perlu didonlot :LiquidCrystal I2C by Frank de Brabander

LiquidCrystal_I2C lcd(0x27, 20, 4); // Set the LCD address to 0x27 by Teach Me Something
int jam, menit, detik, i, jam_stw, menit_stw, detik_stw,jam_alr, menit_alr, detik_alr;

int buttonState = 0;        // current state of the button
int lastButtonState = 0;    // previous state of the button
int longPressDuration = 500; // millis
unsigned long buttonPressTime = 0; // time when button was pressed
volatile bool btnmode_shpress, btnmode_lgpress, btnplus_press, btnmin_press, alarm_on;
//              short press       long press
volatile bool awal_screen, atur_screen, alarm_screen, stopwatch_screen, flag_second,flag_stw, start;

// ini untuk library lcd
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

// arduino yang aku punya hanya ada arduino due yang pakainya ARM bukan AVR, karena nama registernya beda
// dan pinnya beda jadi kasi kondisional untuk ngecek apakah core yang dipake AVR atau ARM (abaikan saja bagian ini)

#ifdef __arm__ // Check if compiling for ARM (e.g., Arduino Due)

#include <sam.h>
void arm_timer_function() {
  pmc_set_writeprotect(false); // Disable write protection for PMC (Power Management Controller)
  pmc_enable_periph_clk(ID_TC0); // Enable peripheral clock for Timer Counter 0
  
  // Configure Timer Counter 0 (TC0) for a 1 Hz frequency
  TC_Configure(TC0, 0, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
  TC_SetRC(TC0, 0, 656250); // = 84000000 / (128 * 1) - 1
  TC_Start(TC0, 0); // Start the timer
  
  // Enable Timer Counter 0 (TC0) interrupt on RC compare
  TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;
  TC0->TC_CHANNEL[0].TC_IDR = ~TC_IER_CPCS; // Disable all other interrupts for TC0
  NVIC_EnableIRQ(TC0_IRQn); // Enable TC0 interrupt vector
}
void TC0_Handler() {
  flag_second=true;
  flag_stw=true;
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
  OCR1A = 62500; // = 16000000 / (256 * 1) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 256 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts
}
ISR(TIMER1_COMPA_vect){
  flag_second=true;
  flag_stw=true;
  TIFR1 |= (1 << OCF1A);  // reset flag
}
#endif

void stopwatch(){
    if(flag_stw){
      detik_stw += 1;
      if (detik_stw >59){ 
        detik_stw = 0;
        menit_stw += 1;
        if (menit_stw > 59){
          menit_stw =0;
          jam_stw +=1 ;
          if (jam_stw> 23){
            jam_stw =0;
          }
        }
      }
      flag_stw = false;
    }
}

void time(){
  if(flag_second){
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
    flag_second = false;
  }
}

void setup() {
  // debugging purpose
  Serial.begin(115200);
  // cek apakah mau menjalankan timer untuk AVR atau ARM (ini hanya ada karena aku gapunya arduino yang pake AVR (nano, uno atau lainnya))
  #ifdef __arm__
    arm_timer_function();
    pinMode(btnmode, INPUT); // ini aku coba coba di arduino due pakenya 4
  #else
    avr_timer_function();
    pinMode(btnmode, INPUT);
    pinMode(btnplus, INPUT);
    pinMode(btnmin, INPUT);
    pinMode(alarm_on, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(btnmin), buzzer_int, HIGH);
  #endif
  // inisiasi lcd
  lcdinit();
  lcd.setCursor(19,i);
  lcd.print("-");
  awal_screen = true;
}

void loop() {
  time();  // terus jalankan jam
  if(start == true){ // jalankan stopwatch kalau uda pencet start saja
  stopwatch();
  }
  button_detect(); //terus jalankan deteksi short/long press button
  mode_selection(); // untuk pilih mode

  // display
  if(awal_screen){
    jam_display();
  } if (alarm_on == true) {
    tone(buzzer, 1000);
    delay(10000);
  } else if(atur_screen){
    atur_display();
  } else if(alarm_screen){
    alarm_display();
  } else if(stopwatch_screen){
    stopwatch_display();
  }
}
