#include <Arduino.h>
#include <SPI.h>
// needed to switch off the wifi module. 
#include <ESP8266WiFi.h>


// 3rd party library for hardware timers
// https://github.com/khoih-prog/ESP8266TimerInterrupt
#define USING_TIM_DIV16          true           // for medium time and medium accurate timer
#include "ESP8266TimerInterrupt.h"
#include "ESP8266_ISR_Timer.h"

ESP8266Timer ITimer;
ESP8266_ISR_Timer ISR_Timer;

void IRAM_ATTR TimerHandler()
{
  ISR_Timer.run();
}

void tmr0ISR(){
  if (Serial.available() > 0){
    while (Serial.available()) Serial.read();
    Serial.print(millis());
    Serial.println(": SERIAL");
  }
}

void tmr1ISR(){
  Serial.print(millis());
  Serial.println(": TMR1");
}

void tmr2ISR(){
  Serial.print(millis());
  Serial.println(": TMR2");
}

uint32_t lastPress = 0;

void IRAM_ATTR btn1ISR(){
  if (millis()-lastPress > 100) {
    lastPress = millis();
    Serial.print(millis());
    Serial.println(": BTN1");
  }

}

#define TIMER_INTERVAL_MS        50L

#define TIMER0_INTERVAL             100L 
#define TIMER1_INTERVAL             1000L 
#define TIMER2_INTERVAL             2000L

void setup() {

  // Make sure WiFi isn't doing anything weird in the background
  WiFi.mode(WIFI_OFF); 

  // This is hardware serial and should default to TX0, RX0. I believe the ELRS receiver TX RX pins are connected to these. 
  Serial.begin(57600);

  // Start the hardware timers and set iterrupts
  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler))
  {
    Serial.print(F("Starting  ITimer OK, millis() = ")); Serial.println(millis());
  }
  else
  {
    Serial.println(F("Can't set ITimer correctly. Select another freq. or interval"));
  }

  ISR_Timer.setInterval(TIMER0_INTERVAL, tmr0ISR);
  ISR_Timer.setInterval(TIMER1_INTERVAL, tmr1ISR);
  ISR_Timer.setInterval(TIMER2_INTERVAL, tmr2ISR);

  // Attach an interrupt to detect button presses 
  // Resues the Flash button on the NodeMCU V3 board
  pinMode(0, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(0), btn1ISR, FALLING);

  // Not really testing SPI, but tests the imports
  SPI.begin();
  SPI.setHwCs(true);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setFrequency(10000000);
  
}

void loop() {

  // Basically blocking 100% of the time 
  // Show's the interrupts are doing what they are supposed to
  Serial.print("Blocking code: ");
  Serial.println(millis());
  delay(10000);

}
