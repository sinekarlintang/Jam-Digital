#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 by Teach Me Something
int second;

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

// arduino yang aku punya hanya ada arduino due yang pakainya ARM bukan AVR, karena nama registernya beda
// jadi kasi kondisional untuk ngecek apakah core yang dipake AVR atau ARM
#ifdef __arm__ // Check if compiling for ARM (e.g., Arduino Due)
#include <sam.h>
void arm_timer_function() {
  pmc_set_writeprotect(false); // Disable write protection for PMC (Power Management Controller)
  pmc_enable_periph_clk(ID_TC0); // Enable peripheral clock for Timer Counter 0
  
  // Configure Timer Counter 0 (TC0) for a 1 Hz frequency
  TC_Configure(TC0, 0, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
  TC_SetRC(TC0, 0, 62500); // Set the frequency to 1 Hz (16 MHz / 256 / 62500 = 1 Hz)
  TC_Start(TC0, 0); // Start the timer
  
  // Enable Timer Counter 0 (TC0) interrupt on RC compare
  TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;
  TC0->TC_CHANNEL[0].TC_IDR = ~TC_IER_CPCS; // Disable all other interrupts for TC0
  NVIC_EnableIRQ(TC0_IRQn); // Enable TC0 interrupt vector
}
void TC0_Handler() {
  TC_GetStatus(TC0, 0); // Clear TC0 interrupt flag
  second += 1;
}

#else // Assume AVR (e.g., Arduino Nano)
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
 second +=1;
}
#endif





void setup() {
  // cek apakah mau menjalankan timer untuk AVR atau ARM
  #ifdef __arm__
    arm_timer_function();
  #else
    avr_timer_function();
  #endif
  // inisiasi lcd dari LCD_Big_font.ino
  lcdinit();
}

void loop() {
  for (int i = 0; i<10;i++){
    printNumber(i,0);
    delay(1000);
    lcd.clear();
  }
}
