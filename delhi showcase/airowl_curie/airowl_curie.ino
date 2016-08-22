#include "CurieIMU.h"
#include <CurieBLE.h>
#include <SoftwareSerial.h>

/**
* BLE Initialization Code
*
*/
BLEPeripheral blePeripheral;       // BLE Peripheral Device (the board you're programming)

BLEService imuService("917649A0-D98E-11E5-9EEC-0002A5D5C51B"); // Custom UUID

BLECharacteristic imuAccCharacteristic("917649A1-D98E-11E5-9EEC-0002A5D5C51B", BLERead | BLENotify, 12 );
BLECharacteristic imuGyroCharacteristic("917649A2-D98E-11E5-9EEC-0002A5D5C51B", BLERead | BLENotify, 12 );
BLEUnsignedCharCharacteristic appButtonCharacteristic("917649A7-D98E-11E5-9EEC-0002A5D5C51B", BLERead | BLEWrite );

BLEDescriptor imuAccDescriptor("2902", "block");
BLEDescriptor imuGyroDescriptor("2902", "block");

/** 
 *  Define pins, connect your LEDs to the appropriate pins as defined below. These pins are 
 *  not required for the demo to function and therefore the circuit to connect them
 *  are not necessary.
*/
#define BLE_CONNECT 3 // This pin will service as a hardware confirmation of the BLE connection
#define INDICATOR_LEDA 4 // This pin will be used to debug input buttons from mobile app

SoftwareSerial Dust_Serial(2, 3);
/**
* The union directive allows 3 variables to share the same memory location. Please see the 
* tutorial covering this project for further discussion of the use of the union
* directive in C.
*
*/
 union 
 {
  float a[3];
  unsigned char bytes[12];      
 } accData;

 union 
 {
  float g[3];
  unsigned char bytes[12];         
 } gyroData;
 

void setup() {

  // initialze serial port for debugging communications
  Serial.begin(9600); // initialize Serial communication
  Dust_Serial.begin(9600);
 
  Serial.println("Arduino101/IntelCurie/Accelerometer/Evothings Example Started");
  Serial.println("Serial rate set to 9600");
  
  // initialize IMU
  // Serial.println("Initializing IMU device...");
  CurieIMU.begin();

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);

  // Set the accelerometer range to 250 degrees/second
  CurieIMU.setGyroRange(250);

  initDustSensor();

  // prepare & initiazlie BLE
  // enable LED pins for output.
  pinMode(BLE_CONNECT, OUTPUT);
  pinMode(INDICATOR_LEDA, OUTPUT);

  blePeripheral.setLocalName("imu");
  blePeripheral.setAdvertisedServiceUuid(imuService.uuid());  // add the service UUID
  blePeripheral.addAttribute(imuService);   
  blePeripheral.addAttribute(imuAccCharacteristic);
  blePeripheral.addAttribute(imuAccDescriptor);
  blePeripheral.addAttribute(imuGyroCharacteristic);
  blePeripheral.addAttribute(imuGyroDescriptor);
  blePeripheral.addAttribute(appButtonCharacteristic);


  // All characteristics should be initialized to a starting value prior
  // using them.
  const unsigned char initializerAcc[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
  const unsigned char initializerGyro[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
 
  imuAccCharacteristic.setValue( initializerAcc, 12);
  imuGyroCharacteristic.setValue( initializerGyro, 12 );
  appButtonCharacteristic.setValue(0);
  
  blePeripheral.begin();

  yellow();
  
}

void loop() {
  
  int axRaw, ayRaw, azRaw;         // raw accelerometer values
  int gxRaw, gyRaw, gzRaw;         // raw gyro values
  int pm25, pm10;

  // ?: Would there be an eficiency gained by declaring these outside the loop?

  // Here we connect oth central, your mobile device!
  BLECentral central = blePeripheral.central();
  if (central) {
    
    Serial.print("Connected to central: "); Serial.println(central.address());
    // It does not matter f you connect this LED or not, it is up to you.
    digitalWrite(BLE_CONNECT, HIGH);


    /**
     * All processing occurs in the context of an active BLE connection. 
    */
    while (central.connected()) {
      
      readDustData(pm25, pm10);
      // read raw accelerometer measurements from device
      CurieIMU.readAccelerometer(axRaw, ayRaw, azRaw);

     /** 
      *  convert the raw accelerometer data to G's and assign them to the elements of
      *  the float array in the union representing the accelerometer data.
     */
     

      accData.a[0] = pm25;
      accData.a[1] = 0;
      accData.a[2] = 0;

      
      // read raw gyro measurements from device
     CurieIMU.readGyro(gxRaw, gyRaw, gzRaw);

     
    /** 
      *  convert the raw gyro data to degrees/second and assign them to the elements of
      *  the float array in the union representing the gyroscope data.
     */
     
     gyroData.g[0] = pm10;
     gyroData.g[1] = 0;
     gyroData.g[2] = 0;
     
     
     // These statements are for debugging puposes only and can be commented out to increae the efficiency of the sketch.
     Serial.print( "(ax,ay,az): " ); 
     Serial.print("("); Serial.print(accData.a[0]); Serial.print(","); Serial.print(accData.a[1]); Serial.print(","); Serial.print(accData.a[2]); Serial.print(")");Serial.println();
     Serial.print( "(gx,gy,gz): " ); 
     Serial.print("("); Serial.print(gyroData.g[0]); Serial.print(","); Serial.print(gyroData.g[1]); Serial.print(","); Serial.print(gyroData.g[2]); Serial.print(")");Serial.println();
      
     /**
      * The following two statements have the potential to cuase the most confusion. Please see the tutorial for
      * more on this.
      * What we are doing here is casting our union variables into a pointer of unsigned characters in
      * order to allow us to pass the array of bytes to the setValue() function.
     */
     unsigned char *acc = (unsigned char *)&accData;
     unsigned char *gyro = (unsigned char *)&gyroData;


      /**
       * Setting the values here will cause the notification mechanism on the moible app 
       * side to be enacted.
      */
     imuAccCharacteristic.setValue( acc, 12 );
     imuGyroCharacteristic.setValue( gyro, 12 );

     turnOnLed();
  
     /**
      * When a button is pressed on the mobile app, the value of the characteristic is changed and
      * sent over BLE to the arduino/genuino101. A change in the characteristic is indicated
      * by a true value from the written() function and the value transmitted from the button 
      * on the mobile app is read here with the value() function.
      * The values change here essentially do nothing but print out a line to the serial port.
      * You can make them do anything here.
      * 
     */    
     if ( appButtonCharacteristic.written() ) {

        int appButtonValue = appButtonCharacteristic.value();

        switch(appButtonValue) {

          case 0:
            Serial.println( "App Input Value(0): " + appButtonValue );
            break;
          case 1:
            Serial.println( "App Input Value(1): " + appButtonValue );
            break;
          case 2:  
             Serial.println( "App Input Value(2): " + appButtonValue );
            break;  
        }
        
      }
      
      
    } // while central.connected  
  } // if central
} // end loop(){}


/**
 * The follwing functions are taken directly from the accelerometer
 * and gyroscope demo apps.
*/

float convertRawAcceleration(int aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767
  
  float a = (aRaw * 2.0) / 32768.0;

  return a;
}

float convertRawGyro(int gRaw) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767
  
  float g = (gRaw * 250.0) / 32768.0;

  return g;
}

void readDustData(int &pm25, int &pm10)
{

  byte data[24];
  byte i = 0;

    while (!Dust_Serial.available());
    while (Dust_Serial.available())
    {
      data[i] = Dust_Serial.read();
      if (data[0] == 0x42)
      {
        if (data[1] == 0x4D)
        {
          if (i == 23)
          {
            pm25 = ((data[6] * 256) + data[7]);
            pm10 = ((data[8] * 256) + data[9]);
            Serial.print("PM 2.5 :");
            Serial.println(pm25);
            Serial.print("PM 10 :");
            Serial.println(pm10);
            Serial.println("");
            Dust_Serial.flush();
            break;
          }
        }
        i++;
        delay(10);
      }
    }
}

void initDustSensor()
{
  const unsigned char cmd_get_sensor[] =
  {
    0xff, 0x01, 0x78, 0x40, 0x00,
    0x00, 0x00, 0x00, 0x47
  };

  // Send cmd to get data
  for (int i = 0; i < sizeof(cmd_get_sensor); i++)
  {
    Dust_Serial.write(cmd_get_sensor[i]);
  }
  delay(10);
} 

void turnOnLed()
{
  yellow();
}

void yellow()
{
    analogWrite(A0, 0);
    analogWrite(A1, 100);
    analogWrite(A2, 0);
}

void red()
{
   analogWrite(A0, 0);
   analogWrite(A1, 100);
   analogWrite(A2, 100);
}

void green()
{
      analogWrite(A0, 100);
    analogWrite(A1, 100);
    analogWrite(A2, 0);
}

