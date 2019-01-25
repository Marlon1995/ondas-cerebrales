                
#include <SoftwareSerial.h>
#include <Servo.h>
int BAUDRATE = 57600;

SoftwareSerial Serial1(11,10);
// checksum variables
byte payloadChecksum = 0;
byte CalculatedChecksum;
byte checksum = 0;              //data type byte stores an 8-bit unsigned number, from 0 to 255
int payloadLength = 0;
byte payloadData[64] = {0};
byte poorQuality = 0;
byte attention = 0;
byte meditation = 0;
Servo servoMotor;
Servo servoMotor2;
Servo servoMotor3;
Servo servoMotor4;
 Servo servoMotor5;
// system variables
long lastReceivedPacket = 0;
boolean bigPacket = false;
boolean brainwave = false;
void setup() {
  
  
  Serial1.begin(57600);       // Bluetooth
  delay(500);
  Serial.begin(9600);      // soft ware serial
  delay(500);
 servoMotor.attach(2);
   servoMotor2.attach(3);
    servoMotor3.attach(4);
     servoMotor4.attach(5);
     servoMotor5.attach(6);
   delay(200);
  
  servoMotor.write(180);
  delay(500);
  // meñique
    servoMotor2.write(0);
    delay(500);
  // indice
      servoMotor3.write(0);
      delay(500);
      // anular
        servoMotor4.write(180);
        delay(500);
        //medio
           servoMotor5.write(180);
           delay(500);
   
       
 Serial.print("Communicating... ");
  
}
byte ReadOneByte() {
   int ByteRead;
  // Wait until there is data
  while(!Serial1.available());
  //Get the number of bytes (characters) available for reading from the serial port.
  //This is data that's already arrived and stored in the serial receive buffer (which holds 64 bytes)
  ByteRead = Serial1.read();
  
  return ByteRead; // read incoming serial data
  }

unsigned int delta_wave = 0;
unsigned int theta_wave = 0;
unsigned int low_alpha_wave = 0;
unsigned int high_alpha_wave = 0;
unsigned int low_beta_wave = 0;
unsigned int high_beta_wave = 0;
unsigned int low_gamma_wave = 0;
unsigned int mid_gamma_wave = 0;

void read_waves(int i) {
  delta_wave = read_3byte_int(i);
  i+=3;
  theta_wave = read_3byte_int(i);
  i+=3;
  low_alpha_wave = read_3byte_int(i);
  i+=3;
  high_alpha_wave = read_3byte_int(i);
  i+=3;
  low_beta_wave = read_3byte_int(i);
  i+=3;
  high_beta_wave = read_3byte_int(i);
  i+=3;
  low_gamma_wave = read_3byte_int(i);
  i+=3;
  mid_gamma_wave = read_3byte_int(i);
}

int read_3byte_int(int i) {
  return ((payloadData[i] << 16) + (payloadData[i+1] << 8) + payloadData[i+2]);
}

void loop() {
  // Look for sync bytes
  // Byte order: 0xAA, 0xAA, payloadLength, payloadData,
  // Checksum (sum all the bytes of payload, take lowest 8 bits, then bit inverse on lowest
if(ReadOneByte() == 0xAA) {
if(ReadOneByte() == 0xAA) {
payloadLength = ReadOneByte();
if(payloadLength > 169) //Payload length can not be greater than 169
return;
payloadChecksum = 0;
      for(int i = 0; i < payloadLength; i++) {      //loop until payload length is complete
        payloadData[i] = ReadOneByte();             //Read payload
        payloadChecksum += payloadData[i];
      }
      checksum = ReadOneByte();                     //Read checksum byte from stream
      payloadChecksum = 255 - payloadChecksum;      //Take one’s compliment of generated checksum
      if(checksum == payloadChecksum) {
        poorQuality = 200;
        attention = 0;
        meditation = 0;
 }
     brainwave = false;
     for(int i = 0; i < payloadLength; i++) { // Parse the payload
          switch (payloadData[i]) {
          case 02:
            i++;
            poorQuality = payloadData[i];
            bigPacket = true;
            break;
          case 04:
            i++;
            attention = payloadData[i];
            break;
          case 05:
            i++;
            meditation = payloadData[i];
            break;
          case 0x80:
            i = i + 3;
            break;
          case 0x83:                         // ASIC EEG POWER INT
            i++;
            brainwave = true;
            byte vlen = payloadData[i];
           // Serial.print(vlen, DEC);
          ///  Serial.println();
            read_waves(i+1);
            i += vlen; // i = i + vlen
            break;
          }                                 // switch
        }                                   // for loop

        if(bigPacket) {
          if(poorQuality == 0){
          }
          else{                             // do nothing
           }
         }


            if(brainwave && attention > 0 && attention < 100) {
            Serial.println("atención:");
            Serial.println(attention/10);

            // Cerrar brazo
       
       if(attention > 0 && attention < 40)
       {
        // Desplazamos a la posición 0º
  //pulgar
 delay(1000);
  servoMotor.write(180);
  delay(1000);
  // meñique
    servoMotor2.write(0);
    delay(1000);
  // indice
      servoMotor3.write(0);
      delay(1000);
      // anular
        servoMotor4.write(180);
        delay(1000);
        //medio
           servoMotor5.write(180);
           delay(1000);
         
       
      
       }
       else
      {
        delay(1000);
        servoMotor.write(0);
      delay(1000);
    servoMotor2.write(180);
    delay(1000);
      servoMotor3.write(180);
      delay(1000);
     
       servoMotor4.write(0);
       delay(1000);
        servoMotor5.write(0);
       delay(1000);
       }
       delay(200);
            }
            

    
  
        } 
        }
      }
