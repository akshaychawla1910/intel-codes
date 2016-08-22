
#include <LiquidCrystal.h>

char c;
String bp;
String sys;
String dia;
String plse;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("eHealth Monitor");

}

void loop() {
  
  // put your main code here, to run repeatedly:
  if(Serial1.available())
  {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    while(Serial1.available())
    {
    c = Serial1.read();
    bp = bp + c;
    delay(10);
    }
    if(bp.length() > 3)
    {
      sys = bp.substring(1, 4);
      dia = bp.substring(6, 9);
      plse = bp.substring(11, 14);
      Serial.println("Systolic Pressure:  ");
      Serial.print(sys);
      Serial.println("Diastolic Pressure:  ");
      Serial.print(dia);
      Serial.println("Heart-rate Pulse:  ");
      Serial.print(plse);
      lcd.setCursor(0, 1);
      // print the number of seconds since reset:
      lcd.print(bp);  
    }
  
  }
   bp = "";
   sys = "";
   dia = "";
   plse = "";
}
