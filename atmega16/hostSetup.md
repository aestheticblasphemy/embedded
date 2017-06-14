## Setup Instructions:

* Install AVR-Tools: 
```
sudo apt-get install avr-libc gcc-avr binutils-avr gdb-avr avrdude avrdude-doc
```

* For eclipse users, install the AVR Plugin from [this update URL](http://avr-eclipse.sourceforge.net/updatesite/).[ref](http://www.instructables.com/id/How-to-get-started-with-Eclipse-and-AVR/?ALLSTEPS)

- In the project settings go to `C/C++ Build` settings and in the builder type, set 'External builder'
- In the `C/C++ Build context`, go to `Settings` and for `Tool Settings`, click the options on the right pane. While we only need HEX files for Flash Memory and AVRDude, other options may be checked (there goes nothing).
- In the `AVR>AVRDude` Settings, select a `New...` for `Programmer configuration` and select the appropriate programmer that you are using. For me, it is the ASPUSB Programmer, so, the option is `Any usbasp clone with correct VID/PID`. 
- Now, make sure that the programmer is connected to the computer as well as the board. Also ensure that they are powered up (USB power is fine). Once that is selected, go to `AVR>Target Hardware` and click on `Load from MCU`. If everything is fine, the correct MCU will load up in the box. There could be an error for `Operation not permitted`. You could fix it in many ways. One is, run eclipse as `sudo`. Second is, add a `udev` rule allowing non-root users to access the `usbasp` device. To do that:
- Open file
```
sudo nano /etc/udev/rules.d/41-atmega.rules
```

- Write the following lines. To get your idVendor and idProduct, just do a `sudo lsusb` and see what the tuple device description looks like. In my case, it was:

```
Bus 003 Device 006: ID 16c0:05dc Van Ooijen Technische Informatica shared ID for use with libusb
```

The ID has two parts. The first is the Vendor ID, and the second is the Product ID. Use them as follows. [ref](http://avr-eclipse.sourceforge.net/wiki/index.php/Known_Issues#.22Operation_not_permitted.22_error)
```
# USBASP
ATTR{idVendor}=="16c0", ATTR{idProduct}=="05dc", GROUP="users", MODE="0666"
```

- Reload the rules [ref](http://stackoverflow.com/questions/25445178/udev-rules-are-not-working-for-libusb-on-ubuntu-12-04)
```
sudo udevadm control --reload-rules
sudo service udev restart
sudo udevadm trigger
```

- Verify device is now allowing 'users' group access to the device:
```
ls -l /dev/bus/usb/003/006
```

- Now, try to fetch information from MCU in eclipse. It should work now.


For the non-eclipse users, the installation steps should be enough. Post that, compilation has various steps: [ref](http://aestheticblasphemy.com/technical/avring-fun/avr-first-breath-hello-world)

For example, let us be compiling and flashing a file to blink LEDs `blinky.c`

* Compile and create object file:
```
avr-gcc -mmcu=atmega16 -Os blinky.c -o blinky.o
```
* Create a HEX file:
```
avr-objcopy -j .text -j .data -O ihex blinky.o  blinky.hex
```

* Flash to uC:
```
avrdude -c usbasp -p m16 -u -U flash:w:blinky.hex
```

## Update

The most recent version of eclipse (Neon) seems to have some trouble using the detect MCU functionality. It throws the following output:

```
AVRDude Error
Could not understand the output from AVRDude...
```

If you also encounter this problem, look into the console logs. 
To enable AVR Dude internal logs on to eclipse console, go to windows>preferences>AVR>AVRDude and click on the 'Log internal AVRDude output to console.'

In my case, it turned out to be a minimal nuisance that the AVRDude was somehow triggered twice, first with the config that I had set, and then with another device settings. This different device caused the error. So, I just ignored this error and went ahead with programming the device. It worked.

---

* As a side note, it is good practice to document the code. But that is too tedious. Now that we're sure we want to use Eclipse, installing the Elcox plugin would do us good .(Here)[https://mcuoneclipse.com/2012/06/25/5-best-eclipse-plugins-1-eclox-with-doxygen-graphviz-and-mscgen/]
* Also install `GraphViz` package.

*Write code. Enjoy!


***

##8051 Variant

* Install MCU 8051 IDE
* https://sourceforge.net/projects/p89pgm/
* untar and `make`

