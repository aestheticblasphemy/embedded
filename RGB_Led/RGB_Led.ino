int red = 11;
int green = 10;
int blue = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  setColor(255,0,0);
  delay(1000);

  setColor(0, 255, 0);
  delay(1000);

  setColor(0,0,255);
  delay(1000);

  setColor(255, 255, 0);
  delay(1000);

  setColor(80, 0, 80);
  delay(1000);  

  setColor(0, 255, 255);
  delay(1000);  
  
}

void setColor(int r, int g, int b )
{
  #ifdef COMMON_ANODE
    r = 255-r;
    g = 255 - g;
    b = 255 - b;
  #endif

  analogWrite(red, r);
  analogWrite(blue, b);
  analogWrite(green, g);
}

