 
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8,9,4,5,6,7);

const unsigned char cmd_get_sensor[] =
  {
    0x11, 0x02, 0x01, 0x00, 0xEC
  };
char datarx[14]; // define array
int co2,dust25,error; // define diffrent sensors
float voc,humidity,tempurature;
float data[5]={0,0,0,0,0};
int x=0;
void setup()
{
  lcd.begin(16,2);
  lcd.print("   Air Quality");
  lcd.setCursor(0,1);
  lcd.print("measurement sys");
  //Serial.begin(9600);
  Serial1.begin(9600);
  delay(1000);
}

void loop() 
{
  for (int i = 0; i < sizeof(cmd_get_sensor); i++)
    {
      Serial1.write(cmd_get_sensor[i]);              //Command to initiate the data reception
    }
    delay(10);
    //Serial.println("Done writing code");
    int l=0;
  if (Serial1.available())
  {  
    while (Serial1.available() && l<14)
    { 
      datarx[l] = Serial1.read();                //Receiving data
     l++;
    }
     
    if(datarx[0] == 22 && datarx[1] == 11 && datarx[2] == 1)      //checking first 3 byte 
    {
        co2=(datarx[3]*256)+datarx[4];
        voc=(float((datarx[5]*256)+datarx[6])/100.0);
        dust25=(datarx[11]*256)+datarx[12];

        data[0]=co2;
        data[1]=voc;
        data[2]=dust25;
       
    }
    
  }
  displaydata();
  delay(1000);
}

/*   Function to Display data on screen    */
void displaydata()
{
    //Serial.print("CO2 : "); //Serial.print(co2); //Serial.println(); 
    //Serial.print("VOC : "); //Serial.print(voc); //Serial.println();
    //Serial.print("Relative Humidity : "); //Serial.print(humidity); //Serial.println();
    //Serial.print("Tempurature : "); //Serial.print(tempurature); //Serial.println();
    //Serial.print("Dust 2.5 : "); //Serial.print(dust25); //Serial.println();
    
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);

    if(x==0)
    {
     lcd.print("CO2: ");lcd.print(data[x]);  
     x++; 
    }
    else if(x==1)
    {
     lcd.print("VOC : ");lcd.print(data[x]);  
     x++;  
    }
     else if(x==2)
    {
     lcd.print("Dust : ");lcd.print(data[x]);  
     x++;  
    }
    
   if(x>2)
   x=0;
    
}

