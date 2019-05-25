#!/usr/bin/python

from pad4pi import rpi_gpio
import time
def print_key(key):
    print(key)
try:
    factory = rpi_gpio.KeypadFactory()
    keypad = factory.create_4_by_4_keypad()
    keypad.registerKeyPressHandler(print_key)

    print("Press buttons on your keypad. Ctrl+C to exit.")
    while True:
        time.sleep(0.1)
except KeyboardInterrupt:
    print("Goodbye")
finally:
<<<<<<< HEAD
    #keypad.cleanup()
=======
    keypad.cleanup()
    print("should cleanup pin")
>>>>>>> e64712866530313c83f06b226bdee401bb73f4ab
