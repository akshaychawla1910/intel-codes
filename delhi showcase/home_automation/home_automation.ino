int pir_motion = 3;
int fan=8;
int light=9;
int motion = 0;
void setup() 
{
  Serial.begin(9600);
  pinMode(pir_motion, INPUT);
  pinMode(fan, OUTPUT);
  pinMode(light, OUTPUT);
  digitalWrite(fan,HIGH);
  digitalWrite(light,HIGH);
}
void loop() 
{
  motion=0;
  for(int i=0;i<20;i++)
  {
    if(digitalRead(pir_motion)==1)
    motion++;
  
  Serial.println(motion);delay(50);
  
  }
  if(motion>10)
  motion=1;

  else motion=0;
  if(motion==1)
  {
    digitalWrite(fan,LOW);
    digitalWrite(light,LOW);
   // delay(100);
  }
  else
  {
    digitalWrite(fan,HIGH);
    digitalWrite(light,HIGH);
   
  }
  delay(1);       
}

