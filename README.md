# EE319K-ECEsekai
EE319K Final Project (GAME) for JRPG engine - ALL of it is custom code, no rehashing or copy &amp; pasting - Exception of PLL.c & Startup.s

Format:
File.(ext) - Short descriptor: Availability (Private: I have E-mailed copies of the password to the appropriate people. It is to their discretion on sharing the contents. I will only mark something as private as those files took the most work to implement, and you should really do the work yourself to fully understand the material.)

Contains
InputOutput.c - The base project from the EE319K-ware lab folder, stripped bare for implementation of a menu system for the start screen: Public

LCD.c - A low level ILI9431 driver with SD card support from separate module: Public

Joystick.c - Control the player character and their actions: Public

MainGame.c - The main engine. Contains a map engine and a combat scenario engine: Private

LoadImages.c - Load an image from the SD card, draw a character from a custom library, and integer to string conversions: Private

Math.c - Contains random number generation using a timer as the seed in addition to mathematical functions that been tested: Public

SDCard.c - Loads a maximum of 32GB, with a theoritical file size of 4GB for 1 file. Stores each file as 72 bytes in RAM using a function that searches the root directory and its sub-directories (Even sub-sub-directories if you're so inclined), sub-directories are searched via recurrsion: Absolutely Private

DAC.c - Loads a sound byte for every output call to the DAC: Public

Sound.c - Contains the main functions for calling sound, SD is not implemented as it clashes with the LCD driver and the SD card driver, originally we planned to implement loading music through the SD card but time did not permit such luxuries: Public
