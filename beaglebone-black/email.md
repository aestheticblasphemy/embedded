##To send an email automatically if some event occurs.

_Since we don't have the Door sensor at hand, we'll fake it with what we do have._

Picture this:
The input switch is beign tested for press. If it is pressed for more than 10 seconds, we send an email to self that it is high! This kind of simplification can actually help build blocks of embedded hardware and software independently. It is because, when we start using hardware as digital devices, we are essentially switching the switch ON or OFF. So, we can replace an actual mechanism by something that emulates it and be sure that when we plug in the real thing, it will work just the same.

Alright! We'll use the setup from `gpio_in.md` and write code for the same. First, we'd like to write some code chunk for sending an email.

1. Email code implemented as a function:
```python
#!/usr/bin/python

import smtplib
from email.mime.text import MIMEText

def send_email(subject, body):
    my_address = 'abc@xyz.com'
    msg = MIMEText(body) #Create an email message with body string as requested
    msg['To'] = my_address
    msg['From'] = my_address
    msg['Subject'] = subject
    msg['Reply-to'] = my_address

    #https://docs.python.org/2/library/smtplib.html
    server = smtplib.SMTP('smtp.gmail.com', 587) #server name, TLS Port
    server.starttls()
    server.login(my_address, 'password')
    server.sendmail(my_address, my_address, msg.as_string()) #from, to, msg[,opts]
    server.quit()
```

2. now, we write the code to check if the switch has been left ON for more than 10 seconds. Esesntially, we start monitoring the switch for ON only after it is pressed ON, until it is released.

```python
#!/usr/bin/python

import Adafruit_BBIO.GPIO as GPIO
import time
import smtplib
from email.mime.text import MIMEText

from sendEmail import *
#Setup P8_13 as input
GPIO.setup('P8_11', GPIO.IN)
sent = False
while sent is False:
    if GPIO.input("P8_11"):
        print 'Pressed. Will alert if pressed for more than 10s'
        time_on = 0
        time.sleep(1)
        while GPIO.input("P8_11") and time_on <= 10:
            time_on +=1
            time.sleep(1)
        if time_on >= 10:
            print "Sending Email"
            send_email("Switch abnormally ON", "Hi! The switch has been ON for at least 10 seconds. Please look into it. Thank you!")
            sent = True
    time.sleep(0.1)

print 'Exiting!'
```

3. Now, can we improve it? Lets see,what we've done is start a counter if we detect that the switch has been pressed. This counter checks every 1 second if the button is still pressed and does so until 10 seconds, or the button is released. Since it checks with a granularity of 1 second, it might miss a rapid action of ON-OFF toggle. How well it will miss, cannot be foretold. It is a matter of timing. If the counter exceeds 10, it sends an email and quits. We could use the actual time instead and compare if it has exceeded the maximum time to raise an alarm:

```python
#!/usr/bin/python

import Adafruit_BBIO.GPIO as GPIO
import time
import smtplib
from email.mime.text import MIMEText

from sendEmail import *

GPIO.setup("P8_11"'", GPIO.IN)
alertTime = 0

while True:
    if GPIO.input("P8_11"):
        if alertTime ==0:
            alertTime = time.time() +10
            print "LED ON. Alerting in 10 seconds if left open"
        else:
            if time.time() > alertTime:
                send_email("Alert!", "The LED has been left open!")
                print "Alerting owner!"
                while GPIO.input("P8_11"):
                    time.sleep(0.1)
    else:
        alertTime = 0
    time.sleep(0.01)
```

And this also does it. 