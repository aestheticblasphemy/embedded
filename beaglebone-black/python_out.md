**To obtain the same results as is `gpio_out.md` using Python Scripts**

1. Install the `Adafruit_BBIO` library. But before we can do that, we will need to install other things to setup python, like, install `pip`.
    ```bash
    opkg update
    opkg install python-pip python-setuptools python-smbus
    pip install Adafruit_BBIO
    ```

2. Check the installation of the Beaglebone IO library by entering the python command prompt and trying to import the module.
    ```bash
    python
    import Adafruit_BBIO
    ```  
    If it doesn't throw any ImportError, we are good to go. Get out of your shell (no pun intended).
    ```bash
    quit()
    ```

3. Write the following code to a file named `blink.py`
    ```bash
    import Adafruit_BBOI.GPIO as GPIO
    import time

    GPIO.setup("P8_12", GPIO.OUT)

    while True:
        GPIO.output("P8_12", GPIO.HIGH)
        time.sleep(1)
        GPIO.output("P8_12", GPIO.LOW)
        time.sleep(1)
    ```
4. Connect the configuration same as that in `gpio_out` on the board.
5. Execute the code by running `python blink.py`. I expect to see the LED blink every one second.

What we have done is not just at-par with what we did before. We have not only turned the LED ON once, but are doing it periodically every one second. This could have been done in the bash scripts also (for example, use `cronjob` to blink the LED every even minute, and turn it off evey odd minute; or, write a bash script similar to the logic we did in our python script.)

Lets try that too:

```bash
#!/bin/bash

echo 44 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio44/direction

a=60
b=0
while [ $b -lt $a ]; do
    echo 1 > /sys/class/gpio/gpio44/value
    sleep 1
    echo 0 > /sys/class/gpio/gpio44/value
    sleep 1
    let b=b+1
done

echo 44 > /sys/class/gpio/unexport
```

That would be all, for now.

