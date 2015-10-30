**To create a timed LED switch**

Use the same setup as in `gpio_out`.

1. First, create the **automation bash scripts** that do the batch action of turning ON and OFF of the Pins:
    *   Create `lightOn.sh` with the following contents:
        ```bash
        #!/bin/bash

        echo 44 > /sys/class/gpio/export
        echo out > /sys/class/gpio/gpio44/direction
        echo 1 > /sys/class/gpio/gpio44/value
        ```
    *   Create `lightOff.sh` with the following contents:
        ```bash
        #!/bin/bash

        echo 0 > /sys/class/gpio/gpio44/value
        echo 44 > /sys/class/gpio/unexport
        ```
    *   Grant execute permissions to both the scripts:
        ```bash
        chmod +x lightOn.sh
        chmod +x lightOff.sh
        ```
    *   Try running the scripts and the LED must light up on running `lightOn.sh` and turn off with `lightOff.sh`

2. **Scheduling** the scripts using **cron**:
    *   Check the current time on device using `date` in the shell. Let current time be `00:20:00`
    *   Open up the crontab in your preferred editor
        ```bash
        EDITOR=nano crontab -e
        ```
        The `-e` option specifies `edit`.
    *   Make an entry to turn the LED on 5 minutes from now:
        ```bash
        25 0 * * * /home/root/lightOn.sh
        ```
    *   Make an entry to turn the LED off 2 minutes from then:
        ```bash
        27 0 * * * /home/root/lightOn.sh
        ```
    *   Save changes and exit. The system must display something like:
        ```bash
        crontab: installing new crontab
        ```
    *   At the designated time, the LED must turn ON, and subsequently, OFF.

**ISSUE** Scripts run fine manually, but not with crontab

See [this stackoverflow question](http://stackoverflow.com/questions/14308147/gpio-command-for-raspberry-not-working-via-crontab) for a way to debug such issues.

Sadly, that did not resolve my issue. So, I tried to test if cron were running actually or not?

Turns out, things don't happen as expected if the date is reset everytime the system boots up (and NTP update is not possible). I connected the board to the internet, updated all the packages, and the cron jobs seemed to work fine then.
