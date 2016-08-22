int echo=5; // define echo pin of ultrasonic 
int trig=4; // define trigger pin of ultrasonic 
int buzz=3; // define  pin for buzzer 
int d=0; 
double t=0;
void setup() 
{
  pinMode(buzz,OUTPUT); // define buzzer as output
  pinMode(echo, INPUT); // define echo as input
  pinMode(trig, OUTPUT); // define trigger as output
  Serial.begin(9600);
  // put your setup code here, to run once:
  t=millis()/1000; // since the execution of the code starts 
}
 
void loop() 
{
  distance(); // gives the value of distance form object 
  if(d<100  &&  ((millis()/1000)-t)<5) // condtion for detecting the object
  {
    
    analogWrite(buzz,180); // turn on vibrator for 5 seconds
  }
  else if(d>100)
  {
    t=millis();
    analogWrite(buzz,LOW); // turn off the vibrator after 5 seconds 
  }
    else 
  {
   
    analogWrite(buzz,LOW); // turn off the vibrator
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
