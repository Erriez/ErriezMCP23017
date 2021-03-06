/*
 * MIT License
 *
 * Copyright (c) 2020 Erriez
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \brief MCP23017 I2C 16-pin IO-expander example for Arduino
 * \details
 *      Source:         https://github.com/Erriez/ErriezMCP23017
 *      Documentation:  https://erriez.github.io/ErriezMCP23017
 *
 *      This example uses the "Arduino way" to read a button on input pin A0
 *      periodically by calling synchronous call delay(). This method blocks the
 *      applicaiton main loop and is not recommended for real applications.
 *
 *      Please refer to the interrupt examples how to handle a pin change. This
 *      reduces the number of I2C bus reads, speeds-up the application response
 *      and supports low-power.
 *
 *      Hardware:
 *      - MCP23017 SDA, SCL connected to MCU I2C (TWI) pins
 *      - PA0: Button input pin with pull-up
 *      - PB0: LED output pin
 */

#include <Arduino.h>
#include <Wire.h>
#include <ErriezMCP23017.h>

// PORTA: pins 0..7
// PORTB: pins 8..15
#define BUTTON_PIN              0  // Pin A0
#define LED_PIN                 8  // Pin B0

// Default I2C Address 0x20
#define MCP23017_I2C_ADDRESS    0x20

// Create MCP23017 object
ErriezMCP23017 mcp = ErriezMCP23017(MCP23017_I2C_ADDRESS);

// Rember last button state
uint8_t buttonPinStateLast;


void setup()
{
    // Initialize Serial
    Serial.begin(115200);
    Serial.println(F("\nErriez MCP23017 I2C IO-expander Button example"));

    // Initialize Wire
    Wire.begin();
    Wire.setClock(400000);

    // Initialize MCP23017
    while (!mcp.begin()) {
        Serial.print(F("Error: MCP23017 not found, code: "));
        Serial.println(mcp.getI2CStatus());
        delay(3000);
    }

    // Set LED pin mode output
    mcp.pinMode(LED_PIN, OUTPUT);

    // Set button pin mode input with internal pull-up
    mcp.pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop()
{
    uint8_t buttonPinState;

    // Read button pin state periodically (polling)
    buttonPinState = mcp.digitalRead(BUTTON_PIN);

    // Print button state and set LED only when button pin changed
    if (buttonPinStateLast != buttonPinState) {
        buttonPinStateLast = buttonPinState;

        // Set LED and print button state
        if (buttonPinState) {
            Serial.println(F("Button up"));
            mcp.digitalWrite(LED_PIN, LOW);
        } else {
            Serial.println(F("Button down"));
            mcp.digitalWrite(LED_PIN, HIGH);
        }
    }

    // Wait synchronous by blocking the application loop (not recommended)
    delay(100);
}
