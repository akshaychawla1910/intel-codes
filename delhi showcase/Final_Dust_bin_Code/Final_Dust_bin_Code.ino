#define echoPin 7 
#define trigPin 8 
#define RELAY1  9   



const int chipSelect = 4;


int maximumRange = 1000; 
int minimumRange = 0; 
long duration, distance; 
const int pinButton = 3;

void setup() {
 Serial.begin (9600);
 

 
 pinMode(pinButton, INPUT);
 
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(RELAY1, OUTPUT);  
 


}

void loop()
{
  digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate distance based on speed of sound
 distance = duration/200.2;


 if (distance >= maximumRange || distance <= minimumRange){

 Serial.println("Out of range");
 digitalWrite(RELAY1,LOW);          
 delay(1000); 
 }

 else {

 Serial.print(distance);
 Serial.println("Cm"); 
 digitalWrite(RELAY1,HIGH);           
 delay(1000);

 
 }
delay(150);

 }

 



