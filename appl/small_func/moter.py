import RPi.GPIO as GPIO 

GPIO.setmode(GPIO.BCM)
PWM=26 #pin37
#
GPIO.setup(PWM, GPIO.OUT, initial=GPIO.HIGH)

freq=50
pwm26=GPIO.PWM(PWM, freq)

pwm.start(freq)

freq=60
pwm.ChangeFrequency(freq)
duty=20
pwm.ChangeDutyCycle(duty)

pwm.stop()

GPIO.cleanup()




