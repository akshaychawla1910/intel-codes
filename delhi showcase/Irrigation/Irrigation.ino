#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created  
int pos = 0;    // variable to store the servo position 



 void move180(){
 for(pos; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
}

void move0(){
  for(pos; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
}

int isRaining(){
  int sVal = analogRead(A0);
  Serial.println(sVal);
  if(sVal < 500){
  return 1;
  }else{
  return 0;   
  }
 
}


 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
  
void loop() 
{ 
  if(isRaining()){
    move180();
  }
  else{
    move0();
  }
}

