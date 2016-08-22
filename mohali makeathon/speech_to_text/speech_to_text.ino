#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8,9,4,5,6,7);
String string="";
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // put your setup code here, to run once:
Serial.begin(9600);
Serial1.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial1.available())
  {
    string="";
    lcd.clear();
    while(Serial1.available())
    {
      char ch=Serial1.read();
      if(ch!='*'&&ch!='#')
      {
      string=string+ch;
      }
    }
    lcd.println(string);
    Serial.println(string);
  }
  lcd.scrollDisplayLeft();
  delay(500);
}
