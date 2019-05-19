#!/usr/bin/python
KEYPAD = [
        ["F1", "F2", "#", "*"],
        [1, 2, 3, "Up"],
        [4, 5, 6, "Down"],
        [7, 8, 9, "Esc"],
        ["Left", 0, "Right", "Ent"]
        ]
ROW_PINS = [26, 20, 21, 17]
COL_PINS = [18, 27, 22, 23]

from pad4pi import rpi_gpio
import time
def print_key(key):
    print(key)
try:
    keypad =rpi_gpio.KeypadFactory().create_keypad(keypad=KEYPAD, row_pins=ROW_PINS, col_pins=COL_PINS, repeat=True, repeat_rate=5, key_delay=100)
    keypad.registerKeyPressHandler(print_key)

    print("Press buttons on your keypad. Ctrl+C to exit.")
    while True:
        time.sleep(0.1)
except KeyboardInterrupt:
    print("Goodbye")
finally:
    keypad.cleanup()
    print("should cleanup pin")
