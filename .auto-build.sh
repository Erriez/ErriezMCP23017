#/bin/bash

echo "Starting auto-build script..."

# Set environment variables
BOARDS_AVR="--board uno --board micro --board pro16MHzatmega328 --board pro8MHzatmega328 --board megaatmega2560 --board leonardo"
BOARDS_ARM="--board due"
BOARDS_ESP="--board d1_mini --board nodemcuv2 --board lolin_d32"

echo "Build examples/01_Polling..."
platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${BOARDS_ESP} examples/01_Polling/ErriezMCP23017_Blink/ErriezMCP23017_Blink.ino
platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${BOARDS_ESP} examples/01_Polling/ErriezMCP23017_BlinkAsynchronous/ErriezMCP23017_BlinkAsynchronous.ino
platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${BOARDS_ESP} examples/01_Polling/ErriezMCP23017_Button/ErriezMCP23017_Button.ino
platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${BOARDS_ESP} examples/01_Polling/ErriezMCP23017_Debounce/ErriezMCP23017_Debounce.ino
platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${BOARDS_ESP} examples/01_Polling/ErriezMCP23017_MultiplePins/ErriezMCP23017_MultiplePins.ino
platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${BOARDS_ESP} examples/01_Polling/ErriezMCP23017_PinPort/ErriezMCP23017_PinPort.ino
echo "Build examples/02_Interrupt_AVR..."
platformio ci --lib="." ${BOARDS_AVR} examples/02_Interrupt_AVR/01_ErriezMCP23017_AVR_INT0/01_ErriezMCP23017_AVR_INT0.ino
platformio ci --lib="." ${BOARDS_AVR} examples/02_Interrupt_AVR/02_ErriezMCP23017_AVR_PCINT/02_ErriezMCP23017_AVR_PCINT.ino
echo "Build examples/03_Interrupt_ESP8266_ESP32..."
platformio ci --lib="." ${BOARDS_ESP}  examples/03_Interrupt_ESP8266_ESP32/01_ErriezMCP23017_ESP8266_ESP32_Interrupt/01_ErriezMCP23017_ESP8266_ESP32_Interrupt.ino

echo "Generate Doxygen HTML..."
doxygen Doxyfile        

# Allow filenames starting with an underscore    
echo "" > html/.nojekyll

