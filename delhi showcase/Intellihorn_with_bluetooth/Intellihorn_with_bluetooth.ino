   #include <CurieBLE.h>


BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
// Nordic's UART Characteristics:    https://devzone.nordicsemi.com/documentation/nrf51/6.0.0/s110/html/a00066.html
BLEService UARTService ("6E400001-B5A3-F393-E0A9-E50E24DCCA9E"); // Nordic UART Service

// BLE UART Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedCharCharacteristic RXCharacteristic ("6E400002-B5A3-F393-E0A9-E50E24DCCA9E", BLEWrite);  // The Nordic Semiconductor UART App sends chars over this RXCharacteristic.
BLEUnsignedCharCharacteristic TXCharacteristic ("6E400003-B5A3-F393-E0A9-E50E24DCCA9E", BLERead);


int  timer=0;
int ir = A0;
int buzzer = 9;

int m11 = 3;
int m12 = 4;
int m21 = 5;
int m22 = 6;


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

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(A0, INPUT);


timer=millis()/1000;

}

void loop() {
  // put your main code here, to run repeatedly:

  if(analogRead(A0)>500)
  timer=millis()/1000;

  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central ();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print ("Connected to central: ");
    // print the central's MAC address:
    Serial.println (central.address ());

    // while the central is still connected to peripheral:
    while (central.connected ()) {
      
    if(analogRead(A0)>500)
    timer=millis()/1000;
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
    forward ();
    
  }
  if (c == 52)
  { // a 0 value
    backward ();
  }
  if (c == 49)
  { //
    left ();
  }
  if (c == 51)
  { //
    right ();
  }
  if (c == 50)
  {
    horn();
  }

  if (c == 53)
  {
    brake();
  }
}



void forward () // forward
{
  digitalWrite (m11, HIGH);  //Reverse motor direction, 1 high, 2 low
  digitalWrite (m12, LOW);  //Reverse motor direction, 3 low, 4 high
  digitalWrite (m21, HIGH);  //Reverse motor direction, 1 high, 2 low
  digitalWrite (m22, LOW);  //Reverse motor direction, 3 low, 4 high
  Serial.println ("forward");
}

void backward () // backward
{
  digitalWrite (m12, HIGH);  //Reverse motor direction, 1 high, 2 low
  digitalWrite (m11, LOW);  //Reverse motor direction, 3 low, 4 high
  digitalWrite (m22, HIGH);  //Reverse motor direction, 1 high, 2 low
  digitalWrite (m21, LOW);  //Reverse motor direction, 3 low, 4 high
  Serial.println ("backward");
}

void left () 
{
  digitalWrite (m11, LOW);  //Reverse motor direction, 3 low, 4 high
  digitalWrite (m12, HIGH);  //Reverse motor direction, 1 high, 2 low
  digitalWrite (m21, HIGH);  //Reverse motor direction, 1 high, 2 low
  digitalWrite (m22, LOW);  //Reverse motor direction, 3 low, 4 high
  Serial.println ("left");
}

void right () 
{
  digitalWrite (m11, HIGH);  //Reverse motor direction, 1 high, 2 low
  digitalWrite (m12, LOW);  //Reverse motor direction, 3 low, 4 high
  digitalWrite (m21, LOW);  //Reverse motor direction, 3 low, 4 high
  digitalWrite (m22, HIGH);  //Reverse motor direction, 1 high, 2 low
  Serial.println ("right");
}


void brake () // backward
{
  digitalWrite (m11, LOW); //Reverse motor direction, 1 high, 2 low
  digitalWrite (m12, LOW);  //Reverse motor direction, 3 low, 4 high
  digitalWrite (m21, LOW);  //Reverse motor direction, 3 low, 4 high
  digitalWrite (m22, LOW);  //Reverse motor direction, 1 high, 2 low
  Serial.println ("brake");
}

void horn()
{
  if ((millis()/1000)-timer<2)
  {

    analogWrite(buzzer,50);
    Serial.println("low horn");
  }

  else
  {
    Serial.println("high horn");
    analogWrite(buzzer,255);

  }
  delay(500);
  analogWrite(9,0);
}



