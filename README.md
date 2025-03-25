
# CHIP8 EMULATOR

## Tech Stack
Using C++ and sfml for graphics (and audio in the future)

## Compilation
`g++ -Wall -Wextra src/chip8.cpp src/cpu.cpp src/instructions.cpp src/main.cpp src/screen.cpp src/keyboard.cpp src/oscillator.cpp -o ch8emu -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -I include`

I decided on going with makefile, next commit will probably be the new Makefile.

## Tests
Tests are taken from [Timendus/chip8-test-suite](https://github.com/Timendus/chip8-test-suite) 
Only the random number test is taken from [mattmikolay/chip-8](https://github.com/mattmikolay/chip-8)
TESTS PASSED:

 - [x] `1-chip8-logo.ch8`
 - [x] `2-ibm-logo.ch8`
 - [x] `3-corax+.ch8`
 - [x] `4-flags.ch8`
 - [x] `5-quirks.ch8`
 - [x] `6-keypad.ch8`
 - [x] `7-beep.ch8`
