# mLRS on ESP8266/8285

This will work on most ESP8266 development boards such as the NodeMCU V3. 

  - Install VSCode or make sure it is upto date
  - Install the PlatformIO plugin 
  - Clone the project to your computer
  - Open the project using platformio menu (not vscode)
  - Build the project 
  - Upload the project
    - Make sure Windows drivers installed for the USB-TTL chip on the board 
    - Put the board in flash mode by resetting or power-on with the flash (or maybe boot) button pressed


All the code is in `src/main.cpp` 

All arduino based programs need a setup and loop function. Setup runs once at power on, loop runs continously. 

HW Timers use this library

https://github.com/khoih-prog/ESP8266TimerInterrupt