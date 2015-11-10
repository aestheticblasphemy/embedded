**Gradually dim the LED and brighten it up using PWM, rather than a 0/1 state**

**INFO**

|   PWM Channel     |   Pins            |
-----------------------------------------
| EHRPWM 0A         | P9\_22, P9\_31    |
| EHRPWM 0B         | P9\_21, P9\_29    |
| EHRPWM 1A         | P8\_36, P9\_14    |
| EHRPWM 1B         | P8\_34, P9\_16    |
| EHRPWM 2A         | P8\_19, P8\_45    |
| EHRPWM 2B         | P8\_13, P8\_46    |
| ECAPPWM2          | P9_28             |
| ECAPPWM0          | P9_42             |

_Pins listed in the same PWM Channel share the same PWM. So, changing one pin pwm changes the other too._

1. Code:

```python
#!/usr/bin/python

import Adafruit_BBIO.PWM as PWM
import time

PWM.start("P8_13",0) #Duty cycle set to 0.

for i in range(1,100):
    PWM.set_duty_cycle("P8_13", float(i))
    time.sleep(0.1)

PWM.stop("P8_13")
PWM.cleanup()
```

This code would make the LED go from 0 brightness to full brightness (1) in a gradual mannner (100 steps).

I noticed, however, that rather than going from completely zero to 1, the LED for an instant lights up to its fullest and then goes off, and gradually lights up again. So, there is supposedly something happening when we start the PWM on Pin 18.
