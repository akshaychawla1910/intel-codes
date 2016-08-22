int fan=5;
int led=6;
int pot=A0;
void setup() {
  // put your setup code here, to run once:
  pinMode(pot,INPUT);
  pinMode(led,OUTPUT);
  pinMode(fan,OUTPUT);
  Serial.begin(9600);

  digitalWrite(fan,HIGH);
  digitalWrite(led,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
double voltage=analogRead(pot);
voltage=(voltage*5)/1023;
Serial.println(voltage);

if(voltage<3.5||voltage>4.5)
{
  digitalWrite(fan,LOW);
  digitalWrite(led,LOW);
}
else
{
  digitalWrite(fan,HIGH);
  digitalWrite(led,HIGH);
}


delay(1000);
}
