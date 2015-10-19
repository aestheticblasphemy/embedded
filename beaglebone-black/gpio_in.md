1. Power off the beaglebone
2. Connect GND (Pins 1 or 2 on either ports) and Power (Pins 3,4 on P9) to breadboard.
3. Place switch on breadboard. (Terminals on the same face are input and output ports. Across might be shorted).
4. Connect one end of Switch to Positive Power Rail.
5. Connect other end of switch to GND via 10k resistor.
6. Connect Pin 13 on Port P8 (GPIO\_1\_13) to negative terminal of switch (parallel to the 10k resistor.) This is a pulldown circuit which pulls the voltage on Pin 13 to 0 when no input is applied. This is to avoid any floating point condition.
7. Power On the beaglebone and export the GPIO\1_\13 as Number 45 in Linux (32x1+13)
    ```
    ssh root@192.168.7.2
    cd /sys/class/gpio
    echo 45 > export
    ```
8. Set pin as input pin.
    ```
    cd gpio45
    echo in > direction
    ```
9. Read value from pin (Free state)
    ```
    cat value
    ```
    This must read 0
10. Read value while pressing the switch down.
    ```
    cat value
    ```
    This must read 1

That is all.

P.S.: Don't forget to unexport the GPIO pins back from the user.
```
cd /sys/class/gpio
echo 45 > unexport
```