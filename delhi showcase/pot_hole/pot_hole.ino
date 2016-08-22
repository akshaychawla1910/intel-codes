int echo=13;
int trig=12;

int d=0;


int m1=6;
int m2=5;

void setup() {
//  pinMode(buzz,OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  Serial.begin(9600);

  digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  // put your setup code here, to run once:

}

void loop() 
{
  distance();
  if(d<10)
  {
    //digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    
    digitalWrite(m1,LOW);
    delay(1);
        digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
  }
 // else
  {

   
    
  }
  // p1ut your main code here, to run repeatedly:

}
void distance()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  d = pulseIn(echo, HIGH); //Listen for echo
  d = (d / 58.138); //convert to CM then to inches
  //if(d<2)
  //d=0;
  Serial.println(d);
  //int data = d;

}
