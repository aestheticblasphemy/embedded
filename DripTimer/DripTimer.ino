#include <LiquidCrystal.h>
// initialize the LCD library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int solenoidPin = 6;    //This is the output pin on the Arduino we are using

unsigned long delayInterval = 1000UL * 60UL * 60UL * 8UL; //Hourly
//unsigned long delayInterval = 1000UL * 60UL * 1UL; //Minutes
unsigned long waterDuration = 1000UL * 30UL; //Seconds
unsigned long previousMillis = 0;
unsigned long cycles = 0;

void lcdStr(String str)
{
  lcd.print(str);
  for(int i = str.length(); i<16;i++) lcd.print(' ');
}

void setup() {
  // put your setup code here, to run once:
  pinMode(solenoidPin, OUTPUT);           //Sets the pin as an output
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Cycles:");
  lcd.setCursor(0, 1);
  lcdStr(String(cycles));
  digitalWrite(solenoidPin, HIGH);    //Switch Solenoid ON
  delay(waterDuration); //Turn on for 30 seconds
  digitalWrite(solenoidPin, LOW);     //Switch Solenoid OFF
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= delayInterval){
    cycles = cycles + 1;
    previousMillis = currentMillis; 
    
    digitalWrite(solenoidPin, HIGH);    //Switch Solenoid ON
    delay(waterDuration); //Turn on for 30 seconds
    digitalWrite(solenoidPin, LOW);     //Switch Solenoid OFF
    lcd.setCursor(0, 1);
    lcdStr(String(cycles));
  }
}
