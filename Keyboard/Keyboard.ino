byte h=0, v=0;

const unsigned long period = 50; //period used to prevent error
unsigned long kdelay=0; //non-blocking delay
const byte rows = 4;
const byte columns=4;

const byte Output[rows] = {2,3,4,5};
const byte Input[columns] = {6,7,8,9};

byte keypad()
{
  static bool no_press_flag = 0; //no button pressed flag
  for(byte x=0;x<columns;x++)
  {
    if (digitalRead(Input[x]) == HIGH)
    {
      ;//Loop until every input is high
    }
    else
    {
      break;
    }
    if(x==(columns-1))
    {
      no_press_flag = 1;
      h=0;
      v=0;
    }
  }
  if(no_press_flag == 1)//No button pressed
  {
    for(byte r=0; r< rows; r++)
    {
      digitalWrite(Output[r], LOW);
    }
    for(h=0;h<columns;h++)
    {
      if (digitalRead(Input[h])==HIGH) //if specific input is remaining high (no longer pressed) continue
      {
        continue;
      }
      else //If one of inputs is low
      {
        for(v=0;v<rows;v++)
        {
          digitalWrite(Output[v], HIGH); //Make specified output as High
          if(digitalRead(Input[h])==HIGH) //If input that selected from first for loop is changed to high
          {
            no_press_flag = 0;
            for(byte w=0; w<rows;w++)
            {
              digitalWrite(Output[w], LOW);
            }
            return v*4+h;
          }
        }
      }
    }
  }
  return 50;
}

void setup() 
{
  // put your setup code here, to run once:
  for (byte i=0; i<rows;i++)
  {
    pinMode(Output[i], OUTPUT); //Set as output pins
  }
  for (byte s=0; s<columns;s++)
  {
    pinMode(Input[s], INPUT_PULLUP); //Set as input PULLUP
  }

  Serial.begin(9600);
    
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() -kdelay >period)
  {
    kdelay = millis();
    switch(keypad())
    {
      case 0:
        Serial.println(1);
        break;
  
      case 1:
        Serial.println(2);
        break;
  
      case 2:
        Serial.println(3);
        break;
  
      case 3:
        Serial.println("A");
        break;
  
      case 4:
        Serial.println(4);
        break;
  
      case 5:
        Serial.println(5);
        break;
  
      case 6:
        Serial.println(6);
        break;
  
      case 7:
        Serial.println("B");
        break;
  
      case 8:
        Serial.println(7);
        break;
  
      case 9:
        Serial.println(8);
        break;
  
      case 10:
        Serial.println(9);
        break;
  
      case 11:
        Serial.println("C");
        break;
  
      case 12:
        Serial.println("*");
        break;
  
      case 13:
        Serial.println(0);
        break;
  
      case 14:
        Serial.println("#");
        break;
  
      case 15:
        Serial.println("D");
        break;
  
      default:
        ;
    }
  }
}
