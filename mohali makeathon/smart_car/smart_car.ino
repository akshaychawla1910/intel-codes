#include <CurieBLE.h>
#include <Servo.h>

BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
// Nordic's UART Characteristics:    https://devzone.nordicsemi.com/documentation/nrf51/6.0.0/s110/html/a00066.html
BLEService UARTService ("6E400001-B5A3-F393-E0A9-E50E24DCCA9E"); // Nordic UART Service

// BLE UART Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedCharCharacteristic RXCharacteristic ("6E400002-B5A3-F393-E0A9-E50E24DCCA9E", BLEWrite);  // The Nordic Semiconductor UART App sends chars over this RXCharacteristic.
BLEUnsignedCharCharacteristic TXCharacteristic ("6E400003-B5A3-F393-E0A9-E50E24DCCA9E", BLERead);


int relay = 11;

int pos = 0;    // variable to store the servo position

Servo myservo;  


void setup() {

  
  // put your setup code here, to run once:
  Serial.begin (9600);

  // set advertised local name and service UUID:
  blePeripheral.setLocalName ("UART");
  blePeripheral.setAdvertisedServiceUuid (UARTService.uuid());

  // add service and characteristic:
  blePeripheral.addAttribute (UARTService);
  blePeripheral.addAttribute (RXCharacteristic);
  blePeripheral.addAttribute (TXCharacteristic);

  // set the initial value for the characeristic:
  RXCharacteristic.setValue (0);

  // begin advertising BLE service:
  blePeripheral.begin ();

  Serial.println ("BLE UART Peripheral");

  pinMode(relay, OUTPUT);
  digitalWrite(relay,HIGH);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

}

void loop() {
  // put your main code here, to run repeatedly:

  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central ();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print ("Connected to central: ");
    // print the central's MAC address:
    Serial.println (central.address ());

    // while the central is still connected to peripheral:
    while (central.connected ()) {
      
      // if the remote device wrote to the characteristic,
      if (RXCharacteristic.written()) {
        Serial.print ("Received: ");
        Serial.print (RXCharacteristic.value ());  // RX Characteristic
        Serial.print (", ");
        Serial.println (TXCharacteristic.value ());  // TX Characteristic

        car(RXCharacteristic.value ());
      }

      // https://github.com/sandeepmistry/arduino-BLEPeripheral/blob/master/BLETypedCharacteristic.h
      RXCharacteristic.setValue (0);

    }
  }


}

void car(char c)
{
  if (c == 48)
  { // ASCII '1'
    relay_on ();
    
  }

   if (c == 49)
  { // ASCII '2'
    relay_off ();
    
  }
 
   if (c == 50)
  { // ASCII '2'
    servo_on ();
    
  }
  
   if (c == 51)
  { // ASCII '2'
    servo_off ();
    
  }
  
}



void relay_on () // forward
{
  digitalWrite (relay, LOW);  //Relay High
  Serial.println ("Relay On");
}


void relay_off () // forward
{
  digitalWrite (relay, HIGH);  //Relay High
  Serial.println ("Relay Off");
}


void servo_on () // forward
{
  for(pos = 0; pos <= 90; pos += 1) // goes from 0 degrees to 180 degrees
  {                                  // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }  
  Serial.println ("Servo On");
}

void servo_off () // forward
{ 
  for(pos = 90; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees
  {
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }  
  Serial.println ("Servo Off");
}






