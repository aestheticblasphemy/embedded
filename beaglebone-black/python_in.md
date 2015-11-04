Use the same setup as in `gpio_in.md` for hardware.

For code part, use the following script (make sure that you've gone through the initial setting up as described in `python_out.md`). In case you cannot find your python executable path, type `which python` to show the currently used path.

1. Code:
```python
#!/usr/bin/python

import Adafruit_BBIO.GPIO as GPIO
import time

GPIO.setup("P8_11", GPIO.IN)

while True:
    if GPIO.input("P8_11"):
        print "Button pressed."
    time.sleep(0.01)
```

Some points to note:
    + The sleep time here is set to `0.01 seconds`. This is to ensure that we don't loop too fast. Nothing wrong in doing that, but in a bigger software system, that is actually problematic, not to mention, unnecessary.
    + The same thing can be done using bash scripts. Try?

```bash
#!/bin/bash

EXIT=0
trap exiting SIGINT
exiting() { echo 45 /sys/class/gpio/unexport; echo 'Exiting'; EXIT=1;}

echo 45 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio45/direction

while [ $EXIT -eq 0 ] ; do
    if [ $( cat /sys/class/gpio/gpio45/value ) -eq 1 ]
    then
        echo 'Button pressed'
    fi
    sleep 0.01
done
```

2. Now, in the previous step, the python script checked after each sleep interval if the button was pressed. Now, we could also only check once and until it is released, stay there, and then print a release notice.

But as I said, a loop without a sleep would consume too much CPU, we could actually compare the two codes CPU usage. So lets do that too to get an actual feel of how different ways of doing the same thing yeild different performances.
3. Code:

```bash
#!/usr/bin/python

import Adafruit_BBIO.GPIO as GPIO
import time

GPIO.setup("P8_11", GPIO.IN)

tick=1

while True:
    if GPIO.input("P8_11"):
        print "Button pressed."
        while GPIO.input("P8_11"):
            #time.sleep(0.01)
            tick+ = 1
        print "Released!"
    time.sleep(0.01)
``` 

While running the code as given above, note that I've commented the sleep inside the loop where we check if button was released. While it is executing, run `top` in a separate shell and observe the differnce in CPU Utilization by the process. When the button is pressed, the CPU use shoots to 96.8% in my case.

Now, uncomment that line of code (and you may remove the tick variable operations). Barely makes a difference in the CPU utilization which now constantly stays at 1.9% So you see, a single sleep of 10ms makes such a huge difference in performance. This becomes more crucial when there are many processes competing for the CPU.

