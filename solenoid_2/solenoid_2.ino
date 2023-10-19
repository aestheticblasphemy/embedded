#include <LiquidCrystal.h>
// initialize the LCD library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int solenoidPin_1 = 6;    //This is the output pin on the Arduino we are using
int sensorPin_1 = A0;
int sensorVcc_1 = 7;  //To put power into the moisture sensor instead of continuous 5V


int solenoidPin_2 = 8;    //This is the output pin on the Arduino we are using
int sensorPin_2 = A1;
int sensorVcc_2 = 9;  //To put power into the moisture sensor instead of continuous 5V
int LED = LED_BUILTIN;

unsigned long lastMillis;

//sudo usermod -a -G dialout $USER
//

void setup() {
  // put your setup code here, to run once:
  pinMode(solenoidPin_1, OUTPUT);           //Sets the pin as an output
  pinMode(sensorVcc_1, OUTPUT);           //Sets the pin as an output
  pinMode(solenoidPin_2, OUTPUT);           //Sets the pin as an output
  pinMode(sensorVcc_2, OUTPUT);           //Sets the pin as an output
  pinMode(LED, OUTPUT);
  
  //Debug: Read moisture sensor values from Serial port
  Serial.begin(9600);
  Serial.println("Reading From the Sensor ...");

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Moisture:");
  // We want to start and stop solenoid once at start and then always after hour
  digitalWrite(solenoidPin_1, HIGH);    //Switch Solenoid ON
  delay(3000);
  digitalWrite(solenoidPin_1, LOW);     //Switch Solenoid OFF

  digitalWrite(solenoidPin_2, HIGH);    //Switch Solenoid ON
  delay(3000);
  digitalWrite(solenoidPin_2, LOW);     //Switch Solenoid OFF

  //digitalWrite(sensorVcc_1, HIGH); 
  //digitalWrite(sensorVcc_2, HIGH); 
  
  lastMillis = millis(); // Get current time   
}

//Variant 4: The sensor once energized by Vcc continues to electrocute the plant
// So, power it on only when sampling.
//
void loop() {
  if(millis() - lastMillis >= 3600L*1000)
  {
    digitalWrite(LED, HIGH);
    delay(3000);
    digitalWrite(LED, LOW);
    
    segment(1, sensorPin_1, solenoidPin_1, sensorVcc_1);
    segment(2, sensorPin_2, solenoidPin_2, sensorVcc_2);
    
    lastMillis = millis(); // Get current time
  }
}

void lcdStr(String str, String id)
{
  lcd.print(id);
  lcd.print(' ');
  lcd.print(str);
  for(int i = str.length(); i<14;i++) lcd.print(' ');
}

void segment(int sensorID, int sensorPin, int solenoidPin, int sensorVcc) {

  int moistureValue ;

  digitalWrite(sensorVcc, HIGH); 
  delay(3000);
  moistureValue= analogRead(sensorPin);
  moistureValue = map(moistureValue,1050,250,0,100); //Map 1050-170 to 0-100
  
  Serial.print(sensorID);
  Serial.print(" : Mositure : ");
  Serial.print(moistureValue);
  Serial.println("%");
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcdStr(String(moistureValue), String(sensorID));

  if(moistureValue < 50) {
    Serial.println("Turn on");
    digitalWrite(solenoidPin, HIGH);    //Switch Solenoid ON
    
    while(moistureValue < 80){
      moistureValue= analogRead(sensorPin);
      moistureValue = map(moistureValue,1050,250,0,100); //Map 1050-170 to 0-100
      Serial.print("L: Mositure : ");
      Serial.print(moistureValue);
      Serial.println("%");
      lcd.setCursor(0, 1);
      //lcd.clear();
      lcdStr(String(moistureValue), String(sensorID));
      //lcd.print(moistureValue);
    }
    
    Serial.println("Turn off");
    digitalWrite(solenoidPin, LOW);     //Switch Solenoid OFF
  }
  digitalWrite(sensorVcc, LOW);  
}

//
//void loop() {
//
//  segment(1, sensorPin_1, solenoidPin_1, sensorVcc_1);
//  segment(2, sensorPin_2, solenoidPin_2, sensorVcc_2);
//  
//  //digitalWrite(sensorVcc, LOW);
//}
