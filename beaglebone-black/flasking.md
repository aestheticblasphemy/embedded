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
