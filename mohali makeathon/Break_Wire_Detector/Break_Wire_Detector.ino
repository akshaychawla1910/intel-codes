void setup() 
{
  
  pinMode(8,OUTPUT);
  pinMode(6,INPUT_PULLUP);
  digitalWrite(8,HIGH);

}

void loop() 
{ 
  int wire = digitalRead(6);
  if(wire == 1)
  
  {
    digitalWrite(8,LOW);
  
  }
  else
  {
  digitalWrite(8,HIGH);
  }
}
