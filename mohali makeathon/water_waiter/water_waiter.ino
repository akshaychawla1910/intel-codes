
String string="";
String waiter="hello";
int motor1=7;
int motor2=9;
void setup() {

  // put your setup code here, to run once:
Serial.begin(9600);
Serial1.begin(9600);

pinMode(motor1,OUTPUT);
pinMode(motor2,OUTPUT);

digitalWrite(8,LOW);
digitalWrite(10,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial1.available())
  {
    string="";
    while(Serial1.available())
    {
      char ch=Serial1.read();
      if(ch!='*'&&ch!='#')
      {
      string=string+ch;
      }
    }
    Serial.println(string);

    if(string.equals(waiter))
{
  digitalWrite(motor1,HIGH);
  digitalWrite(motor2,HIGH);
  delay(3000);
  digitalWrite(motor1,LOW);
  digitalWrite(motor2,LOW);
}
  }


}
