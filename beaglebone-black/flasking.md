## Getting started with Flask

The first problem that I ran into was installing flask. Python couldn't find the `ast` module! It seems that I'll need to update my Angstrom image to a more recen one as somebody [here](http://stackoverflow.com/questions/34126696/cannot-import-ast-flask-installation-on-angstrom-beaglebone-black/34146409#34146409) reported that it had some half-broken python packages.

Once you have Flask installed
```python
pip install Flask
```

Now, let us write our first, `hello world!` page.

1. Open a new file, say `hello_flask.py` and write the following code:
  
   ```python
   from flask import Flask
   app = Flask(__name__)

   @app.route("/")
   def hello():
       return "Hello, world!"

   if __name__ == "__main__":
       app.run(host='0.0.0.0', port=81, debug=True)
   ```
   
   Now, what did we do here? The first line is normal, importing the Flask module into our script.
   * The second line is interesting. It takes a parameter `__name__` and passes it to `Flask` class. The resulting object is stored in the variable named `app`. `__name__` is akin to what we have in C language as `__FILE__`, `__FUNC__` and `__LINE__`, which give the values of the file name the source is in, function name where we are in (if not anything else, it would be `main`), and line number where the directive was invoked. Similarly, here in Python, `__name__` gives the name of the script that is being executed. For now, it is supposed to be the file name (except if we are running it from python shell, but more on that later.)

   * `@app.route("/")` is a URL router. It instructs the code to call the method that follows immediately if the requested url is `/`, which simply means the homepage. In python, these are called `decorators` and really ease the way code is called and plugged into other code.

   * Next is a plain function which returns 'Hello, world!' text.
   * The last two lines are interesting. Here, we check if we are executing the script as it is, or importing it into another module. All the scripts that are executed from the system shell using `python <scrpit_name>` get the `__name__` set to `__main__`. This is much like executing C code, where our program **must** have a `main()`. Since, in Python, we don't explicitly put a `main()`, the interpreter does it for us. In case we aren't executing this code from the system shell, but importing it using, say `import hello_flask`, the `__name__` would not be `__main__`, but would be, probably `hello_flask`, or the script which imported it. (We can check that out!)

   Create a file `test_main.py` and write `print __name__` in it. Create another file `call_main.py` and write `import test_main` in it. First call the `test_main` directly using `python test_main`. What is the output for you? For me, it is `__main__`. Now, call `python call_main`. What did you get. Mine is `test_main`. So, that is how it works!

   * The last line instructs flask to run a server on `0.0.0.0:81` in debug mode. So, if we go to our browser and type 127.0.0.1:81, we should be getting `Hello world!` greeting in an unformatted fashion in our browser.

2. But it is not pretty! We can prettify it using some HTML. Now, we have two options. Either write our HTML pages in the script itself (which I think is too tedious and would get repititive), or use some kind of templating engine which would help us do the two things separately. This second approach is a kind of MVC approach (Model View Controller), where we separate the Model- which is our data that needs to be worked on, View - how things are supposed to look, and the Controller - which renders the data from our Model into the requested View. So, for now, "Hello, World!" could be our Model data, the `hello()` method could be called our controller, while the view is what we would see on the screen. So, we could pass our data into a templating engine which makes our view more elegant. Plus, we need this kidn of separation such that we would not have to change the python script which works purely with the data if we wanted to alter the way our data was to be displayed. For this purpose, we will use Jinja.

   ```python
   from flask import Flask, render_template
   app = Flask(__name__)

   import datetime

   @app.route("/")
   def hello():
       now = datetime.datetime.now()
       time_string = now.strftime("%Y-%m-%d %H:%M")
       template_data = {
          'title': 'Hello!',
          'time': time_string
       }
       return render_template('main.html', **template_data)

   if __name__=='__main__':
       app.run(host='0.0.0.0', port=81, debug=True)
   ```

   Here, we've passed the data into the template in dictionary form by calling `render_template` method. The `main.html` will be searched for in the path 'templates/main.html' and hence must be created there.

   It would look something like:
   ```html
   <!DOCTYPE html>
   <head>
   <title>{{ title }}</title>
   </head>
   <body>
   <h1>Hello, world!</h1>
   <h2>The date and time on the server is: {{ time }}.</h2>
   </body>
   </html>
   ```

   The variables passed into the templates can be accessed inside the `{{` and `}}` symbols. (This is pretty similar to Django's version)

  Now, since this server is running on the device itself, and the backend is written in python, we should have no problems as such to mix and mashup the Adafruit GPIO library module functionality with that of the Flask modules. For instance, we can check if there is input present on a GPIO pin or not from the web interface. Here is how:

 ```python
 import  Adafruit_BBIO.GPIO as GPIO
 from flask import Flask, render_template

 app=Flask(__name__)

 GPIO.setup("P8_11", GPIO.IN)

 @app.route("/")
 def hello():
     if GPIO.input("P8_11"):
         door_status="open"
     else:
         door_status="closed"
     template_data= {'door_Status':door_status,}
     return render_template('main_door.html', **template_data)

 if __name__=='__main__':
     app.run(host='0.0.0.0', port=81, debug=True)
 ```

 See? Simple!

 The template for `main_door.html` may look like:

   ```html
   <!DOCTYPE html>
   <head>
   <title>My Door</title>
   </head>
   <body>
   <h1>We are monitoring our door!</h1>
   <h2>The door is {{ door_status }}.</h2>
   </body>
   </html>
   ```

 Also, we could take user input from the web interface. On the backend, we'll need to receive the value somewhere and set things up accordingly.

 ```python
  from flask import Flask, render_template
  app = Flask(__name__)

  import Adafruit_BBIO.GPIO as GPIO
  import Adafruit_BBIO.PWM as PWM

  PWM.start("P8_13", 0.0)
  GPIO.setup("P8_11", GPIO.IN)
  
  @app.route("/")
  def hello():
      if GPIO.input("P8_11"):
          door_status="open"
      else:
          door_status="closed"
      template_data= {'door_Status':door_status,}
      return render_template('main_door.html', **template_data)

  @app.route("/ledLevel/<level>")
  def pin_state(level):
      PWM.set_duty_cycle("P8_13", float(level))
      return "LED level set to "+ level + "."

  if __name__=='__main__':
      app.run(host='0.0.0.0', port=81, debug=True)
  
 ```

 This is, of course, a very rudimentary code. We need to make sure that the `level` value that is captured from the URL is numerical. Further, putting values which actually do something in URLs is not a good idea. We'd rather put this values in POST objects using a form on the frontend. But, they've nothing to do with Beaglebone development, they are the realm of web development. (That doesn't mean that they're not important. They are, very important).
