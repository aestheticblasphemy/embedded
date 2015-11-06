**Note**
* Beaglebond Black has 7 Pins usable as analog inputs. Pins are 
    - P9\_32: V\_IN
    - P9_34: Analog GND
    - P9_39: AIN 0
    - P9_40: AIN 1
    - P9_37: AIN 2
    - P9_38: AIN 3
    - P9_33: AIN 4
    - P9_36: AIN 5
    - P9_35: AIN 6
* Range of Analog Voltages: 0-1.8V
* 

**Requirements/Equipment**
- 2K Pot [Well, I had 100K, so I used that.] Choice: Using a 2K pot, the value increments in resistances will be high and the drop across the Pot will also be high. But since we are deriving our source from 1.8V, our ADC will not exceed 1.8V here. So, we can use it. Just for trivia, in the 2K case, maximum current flow is 0.9mA.

**Steps** 
- So, connect one end of pot to V\_IN [P9\_32] and the other end to V\_GND [P9\_34].
- The middle pin of the Pot is to be connected to one of the pins of ADC (say P9_33)

- Write the following code:
```python
#!/usr/bin/python

import Adafruit_BBIO.ADC as ADC
import time

ADC.setup()

while True:
    # Normalized value between 0-1;
    # To convert to Voltage values, multiply by 1.8
    value = ADC.read("P9_33")
    time.sleep(0.5)
```
- Run this code and while the output is printing, slowly turn the Pot dial.
Here's my output snippet:

```
0.00166666670702
0.00277777784504
0.00222222227603
0.00222222227603
0.00166666670702
0.00277777784504
0.00166666670702
0.00222222227603
0.00166666670702
0.00222222227603
0.00222222227603
0.00166666670702
0.00166666670702
0.00166666670702
0.00166666670702
0.00111111113802
0.00166666670702
0.00166666670702
0.00277777784504
0.00222222227603
0.00166666670702
.
.
.
0.759999990463
0.766111135483
0.781666696072
0.79777777195
0.807777762413
0.819999992847
0.840555548668
0.865555584431
0.896111130714
0.917222201824
0.927777767181
0.927777767181
0.938333332539
0.945555567741
0.957777798176
0.965555548668
0.969444453716
0.973333358765
0.954444468021
0.86333334446
```
Easy?

- How ADC Works? [Does it measure Voltage across terminals, or does it measure current in V_IN]
- What if we didn't connect the Pot across P9\_34 and P9\_32? What kind of method is used for sampling?