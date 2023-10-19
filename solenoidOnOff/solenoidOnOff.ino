#include <LiquidCrystal.h>
// initialize the LCD library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int solenoidPin = 6;    //This is the output pin on the Arduino we are using
int sensorPin = A0;
int sensorVcc = 7;  //To put power into the moisture sensor instead of continuous 5V

unsigned long lastMillis;
int moistureValue ;

//sudo usermod -a -G dialout $USER
//

void setup() {
  // put your setup code here, to run once:
  pinMode(solenoidPin, OUTPUT);           //Sets the pin as an output
  pinMode(sensorVcc, OUTPUT);           //Sets the pin as an output

  //Debug: Read moisture sensor values from Serial port
  Serial.begin(9600);
  Serial.println("Reading From the Sensor ...");

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Moisture:");
  // We want to start and stop solenoid once at start and then always after hour
  digitalWrite(solenoidPin, HIGH);    //Switch Solenoid ON
  delay(3000);
  digitalWrite(solenoidPin, LOW);     //Switch Solenoid OFF

  digitalWrite(sensorVcc, HIGH); 
  
  lastMillis = millis(); // Get current time   
}

// Variant 1: Very simple, but blocking
//void loop() {
//  // put your main code here, to run repeatedly:
//  digitalWrite(solenoidPin, HIGH);    //Switch Solenoid ON
//  delay(5000);                      //Wait 1 Second
//  digitalWrite(solenoidPin, LOW);     //Switch Solenoid OFF
//  delay(5000);                      //Wait 1 Second
//}


//Variant 2: A bit usable. Blindly fire valve every n hours
// The problem with this is that depending on the weather and day/night
// the consumption/evaporation of water is variable and often leads to 
// overwatering/underwatering
//void loop() {
//  if(millis() - lastMillis >= 3600L*1000*2)
//  {
//    //1 hour popped. Turn on timer for 3 seconds
//    digitalWrite(solenoidPin, HIGH);    //Switch Solenoid ON
//    delay(3000);
//    digitalWrite(solenoidPin, LOW);     //Switch Solenoid OFF
//    lastMillis = millis(); // Get current time
//  }
//}

//Variant 3: Incorporate a moisture sensor also and keep a track of range
// I know that plants get a mild shock from the current flowing in this sensor
// that was the reason for avoiding the sensor. So, what we want to do is 
// minimize the shock by firing the sensor intermittently. (Lets set it at
// a 2-3 hour interval

//Variant 4: The sensor once energized by Vcc continues to electrocute the plant
// So, power it on only when sampling.
//
//void loop() {
//  if(millis() - lastMillis >= 3600L*1000*3)
//  {
//    //3 hour popped. Sample the sensor and see if we must fire the valve
//    digitalWrite(sensorVcc, HIGH); 
//    moistureValue= analogRead(sensorPin);
//    moistureValue = map(moistureValue,1050,170,0,100); //Map 1050-170 to 0-100
//
//    if(moistureValue < 30) {
//      digitalWrite(solenoidPin, HIGH);    //Switch Solenoid ON
//      
//      while(moistureValue < 80){
//        moistureValue= analogRead(sensorPin);
//        moistureValue = map(moistureValue,1050,170,0,100); //Map 1050-170 to 0-100
//      }
//    
//      digitalWrite(solenoidPin, LOW);     //Switch Solenoid OFF
//    }
//    
//    digitalWrite(sensorVcc, LOW);
//    lastMillis = millis(); // Get current time
//  }
//  
//}

void lcdStr(String str)
{
  lcd.print(str);
  for(int i = str.length(); i<16;i++) lcd.print(' ');
}

// Debug Loop
void loop() {
  moistureValue= analogRead(sensorPin);
  moistureValue = map(moistureValue,1050,170,0,100); //Map 1050-170 to 0-100
  Serial.print("Mositure : ");
  Serial.print(moistureValue);
  Serial.println("%");
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcdStr(String(moistureValue));

  if(moistureValue < 30) {
    Serial.println("Turn on");
    digitalWrite(solenoidPin, HIGH);    //Switch Solenoid ON
    
    while(moistureValue < 80){
      moistureValue= analogRead(sensorPin);
      moistureValue = map(moistureValue,1050,170,0,100); //Map 1050-170 to 0-100
      Serial.print("L: Mositure : ");
      Serial.print(moistureValue);
      Serial.println("%");
      lcd.setCursor(0, 1);
      //lcd.clear();
      lcdStr(String(moistureValue));
      //lcd.print(moistureValue);
    }
    
    Serial.println("Turn off");
    digitalWrite(solenoidPin, LOW);     //Switch Solenoid OFF
  }
  //digitalWrite(sensorVcc, LOW);
  lastMillis = millis(); // Get current time
}
