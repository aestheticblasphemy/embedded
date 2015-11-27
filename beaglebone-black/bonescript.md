1. Try to access the BoneScript cloud environment from the board by connecting the board to the network, and accessing [http://beaglebone.local:3000/](http://beaglebone.local:3000/) from the browser.

2. This should open up the colud9 IDE in the browser. Feel free to explore the environment and dive in here and there. The `demo` folder contains a few sample codes to just run and see. On the device, they are located at `/var/lib/cloud9`.

3. Here, we code in Javascript. This is much like solving the same problems and saying the same things in different languages. Once we have understood that all we are doing is gating the switches, it becomes immaterial how we actually do it. What different languages offer is a more feature rich implementation. For example, the Python Code usually runs line by line from top to the bottom, one line at a time. In the case of Javascripts, more flexible and asyncronous things can be done. For example, we may instruct the code to keep watching for some event in the background, and call a particular routine when it occurs. This is implemented through asynchronous callbacks. Not that it cannot be done in Python, but such kind of featuers are baked right into the language structure in case of javascript. Plus, Javascript is the language of the Web Clients (and of late, backends too). So, which method one takes up is their own sweet will.

4. Before we begin with Javascript programming, just a little note about coding conventions. You must have noted that while we were writing code in python, we wrote methods and variable names as words separated by underscores (example `hello_world`). This does not have a formal name (none that I know of yet), but is often used among the python community and their roots (C programming people). This makes the variable, functions and method names more readable. Among the Javascript community, the use of camelcasing and pascalcasing is much more popular. A camelcase looks like `camelCasedName` while a pascal cased variable looks like `PascalCasedVariable`. The difference? Pascal cased literals start capitalized. What difference does it make? Ease of readability. Pascal casing is usually reserved for class names and method names, while camel casing is used for method arguments and local variables. Thus, looking at the code, one can distinguish a variable from a method. In the end, it doesn't matter too much as long as one can maintain consistency of which ever convention one chooses to use. Note that there is some disambiguation between Pascal casing and Camel casing. So, what one might see is the inverted statement, but as is said, it wouldn't matter as long as one is consistent.

In our case, we will be using the underscored convention when coding in python or C, and camel casing when coding in javascript. The reason of choosing underscores for C and Python is a matter of preference. However, for javascript, there is a reason: Javascripts are transported across the internet in zipped or unzipped format when the webpage is requested. Each character used, each space consumed has a penalty of one byte(char) and the more verbose the variables are, the bigger the size of the script. As a developer, this does not matter much, but from a customer point of view, accessing the page over a slower internet connection or when one is paying a premium cost for internet, every byte not transferred counts. This is also the reason why production level javascripts are often contracted into a huge single line of code, and often, their variable names are changed and shortened beyond the point of following through it.

5. Also, another note about the place where the curly braces should open. This is yet again, debated long and hard. Look at the following two code segments:

    ````javascript
    var a=0;
    if(a>0)
    {
      console.log('Positive, Sir!');
    }
    ````
and

    ````javascript
    var a=0;
    if(a>0){
      console.log(Positive, Sir!');
    }
    ````

The two codes listed above are nearly identical, except for the placement of that curly braces. If executed in this way, depending on how Javascript engine works with your browser, the wo may give different results. While the second code explicitly states that the if conditional starts right after the declaration, there is little ambiguity to the interpreter here. However, Javascript being a friendly interpreter (read, it tries to autocorrect), may put a semicolon implicitly ahead of the if in the first case, thinking that it is a statement termination, since it encountered a newline character before a semicolon. Hence, in the Javascript domain, we will stick to the second coding convention (though personally, it makes the code a bit less symmetrical and readable to me). Also note, if one creates a packed version of the script, for example, for production, the spaces will be truncated, and the code would work fine in both cases.

6. So, we could now just show you how to turn ON and OFF the LEDs through Bonescript and you'd be good to go? Let's see.

   * Blink an LED:

     ````javascript
     var b= require("bonescript");
     
     var ledPin = "P8_13";
     var ledPin2 = "USR3";

     b.pinMode(ledPin, b.OUTPUT);
     b.pinMode(ledPin2, b.OUTPUT);

     var state = b.LOW;
     b.digitalWrite(ledPin, state);
     b.digitalWrite(ledPin2, state);

     setInterval(toggle, 1000);

     function toggle(){
       if(state== b.LOW) {
         state = b.HIGH;
       }
       else {
         state = b.LOW;
       }
       b.digitalWrite(ledPin, state);
       b.digitalWrite(ledPin2, state);
     }
     ````

     I think the code is fairly self explanatory. A couple of points to notice. The first line `var b=require("bonscript");` is mandatory. Also note that these scripts might be written on the client side, but are actually going to run on the device (which is different from what happens in the internet world). There runs a Javascript backend 'Node.js' on the Beaglebone which is built around javascript. This is getting much popular in projects like these and also in web design since it allows the same language to be used in the front end as well as in the backend. The first line is much like importing the Adafruit_BBIO module in Python. Javascript being a Dynamic prototyped language, everything in it is an object. So, that first line is essentially creating a bonescript library instance which we can use throughout the code then. 
   the `setInterval(<function_name>, <interval>)` is a vanilla JS method that executes the provided function (or method) after every _interval_ milliseconds. This is slightly different than what we did in python where we made the script sleep for a certain duration. While the script is sleeping, its execution halts until it wakes up. In this case of asynchronous callback, we instruct the system to keep doing whatever it was doing, and only interrupt the execution and momentarily execute the function when the event is fired. After that, the code returns to doing whatever it was doing. This can be done in Python and C also, but we will skip that here.

   Most other lines are self explanatory. Also keep in mind that it should be `require('bonescript')` and not `require('bonescript.js')`. The second option will throw an error if you execute it.

   * Read digital input:

   ```javascript
   var b = require("bonescript");

   var inPin = "P8_11";
   b.pinMode(inPin, b.INPUT);
   b.digitalRead(inPin, printStatus);

   function printStatus(x){
     if(x.value == b.HIGH){
       console.log("The pin is HIGH");
     }
     else{
       console.log("The pin is LOW");
     }
   }
   ```

   > Note that while trying to run this code from the Cloud interface, I was unable to get the desired result. I tried running the older blinking LED code too, which had worked earlier, and that too did not work. It could be the case that the IDE did not load properly. In such cases, what one can do is log into the shell and run the code from command line. This can be done as simply as typing `node <filename.js>`. Doing so gave me the desired outputs.

