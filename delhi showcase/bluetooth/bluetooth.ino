int m11=6;
int m12=5;
int m21=8;
int m22=7;
void setup()  
{ 
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT); 
  pinMode(m22, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode    
  Serial.begin(9600);  
  Serial.println("Enter AT commands:");  
  Serial1.begin(9600);// HC-05 default speed in AT command more  
  stop_m();
}  

  
void loop()  
{  
  
  // Keep reading from HC-05 and send to Arduino Serial Monitor  
 if (Serial1.available())  
  {
    char value=Serial.read();
    if(value=='1')
    {
      forward();
    }
    else if(value=='2')
    {
      rev();
    }
    else if(value=='3')
    {
      right();
    }
    else if(value=='4')
    {
      left();
    }
    else
    {
      stop_m();
    }
    Serial.println(value);
    /*while(Serial1.available()) 
    {
     char str=str+1; 
    }*/
  }
  
  
}
void forward()
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}
void rev()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
}
void left()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}
void right()
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
}
void stop_m()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
}

