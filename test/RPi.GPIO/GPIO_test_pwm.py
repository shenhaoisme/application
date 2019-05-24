import RPi.GPIO as GPIO
import time as time

led_pin=12

class Test():
    def runTest(self):
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(led_pin, GPIO.OUT)
        GPIO.output(led_pin,GPIO.HIGH)
        GPIO.cleanup()

    def runPwm(self):
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(led_pin, GPIO.OUT)
        #pwm=GPIO.PWM(pin, freq)
        pwm = GPIO.PWM(led_pin, 50)
        #the duty cycle (0.0 to 100.0)
        pwm.start(100)
        print("\nPWM tests")
        response = input('Is the LED on (y/n) ? ').upper()
        print(response)
        if response == 'Y':
             pwm.start(100)
             response = input('Is the LED off (y/n) ? ').upper()
             if response == 'Y':
                 pwm.start(0)    
             
             print("LED Brighten/fade test...")
             for i in range(0,3):
             #while True:
                for x in range(0,101,5):
                    pwm.ChangeDutyCycle(x)
                    time.sleep(0.1)
                for x in range(100,-1,-5):
                    pwm.ChangeDutyCycle(x)
                    time.sleep(0.1)
             pwm.stop()
             print("process stop")
        else :
            print("No opreation")
        GPIO.cleanup()


#test.runTest()

try:
    test = Test()
    while True:
        test.runPwm()
except KeyboardInterrupt:
    print("Goodbye")
finally:
    GPIO.cleanup()
    


