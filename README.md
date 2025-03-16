
# CHIP8 EMULATOR

## Tech Stack
Using C++ and sfml for graphics (and audio in the future)

## Compilation
`g++ -Wall -Wextra src/chip8.cpp src/cpu.cpp src/instructions.cpp src/main.cpp src/screen.cpp src/keyboard.cpp -o ch8emu -lsfml-graphics -lsfml-window -lsfml-system`

for now, it will be a `makefile`,`cmake` or `ninja` in the future, i have yet to decide and learn most of these.

## Tests
Tests are taken from [Timendus/chip8-test-suite](https://github.com/Timendus/chip8-test-suite) 

TESTS PASSED:

 - [x] `1-chip8-logo.ch8`
 - [x] `2-ibm-logo.ch8`
 - [x] `3-corax+.ch8`
 - [x] `4-flags.ch8`
 - [ ] `5-quirks.ch8`
 - [ ] `6-keypad.ch8`
 - [ ] `7-beep.ch8`
