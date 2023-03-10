# Morse Flasher

This project is a simple implementation that converts user input to flashes of an LED formatted as morse code. This FreeRTOS project receives input from the user over a serial connection from the connected computer and will decode the message and convert to a series of flashes of an LED. Additionally, this project was created in an afternoon and evening as a challenge from a friend and is therefore sometimes rough around the edges in some areas.

## Main Functionality
*Please note that this functionality is implemented in `main.c`*

Every time the user enters input over the serial terminal, the keypress is recorded by the FreeRTOS communication task. When the enter key is entered, the recorded characters are converted into a series of LED pulses and are queued up to be used by the FreeRTOS flashing task. By separating the functionality via FreeRTOS's tasks, serial communication can still be monitored while the LED is being flashed.

## Potential Improvements
The goal of this project was to learn how to use FreeRTOS in a smaller capacity, and was completed for fun as part of a challenge, limited consideration was given to a better system of decoding character strings. Currently, a list of supporated characters are hardcoded as a series of delays and flashes that are queued for the flashing task. Likely a better way involving dashes and dots contained within a string could be used to generate these sequences as opposed to the current hardcoded implementation.
