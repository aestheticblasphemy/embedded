**Equipment**: 1 LED, 3 jumper wires, 1 solderless breadboard, 100Ohmx1 resistor, Beaglebone Black, USB Connector cable.

1. Turn off the Beaglebone.
2. Connect Positive to Pin 3/4 of Rail P9, and Ground(GND) to 1/2 Rail P8.
3. Connect LED cathode (negative terminal, shorter end) to GND and other anode to a separate port on the breadboard.
4. Connect anode to one end of 100 Ohm resistor. Connect other end of resitor to Pin 12 of Rail P8 (GPIO\_1\_12).
5. Power on the beaglebone and ssh into it.
6. Go to /sys/class/gpio
    ```
    cd /sys/class/gpio
    ```
7. Use the conversion scheme (Beaglebone GPIO to Linux GPIO set) of
    **Linux GPIO = (32x Chip Number) + (Board GPIO)** to derive the GPIO to be exported to user space in Linux. For `GPIO\_1\_12`, it translates to (32x1)+12=44.
8. Export GPIO to user space:
    ```
    echo 44 > export
    ```
    A new directory with name `gpio44` must now be created.

9. Go into the `gpio44` directory and set the direction of the pin to Output.
    ```
    cd gpio44
    echo out > direction
    ```
10. Set the GPIO to high by setting the value 1 on the pin.
    ```
    echo 1 > value
    ```
    The LED must illuminate on doing this. If it doesn't, power-off, check connections and try again.

11. Turn off the LED by setting value `0` using the method in the step above.

