#include <Wire.h>
unsigned char i2c_rcv = 0;
void setup() 
{
  Wire.begin();
  
  Serial.begin(57600);
  Serial.println("start");
  
}

void loop() {
Wire.beginTransmission(0x0F); //Открывает канал связи по шине I2C с ведомым устройством.
Wire.write(byte(0x00));
Wire.endTransmission();      // остановить передачу
Wire.requestFrom(0x0F, 1);    // request potentiometer position from slave 0x0F
  if(Wire.available()) {        // read response from slave 0x08
    i2c_rcv = Wire.read();
  }
Serial.println(i2c_rcv);          // напечатать символ
delay (1000);
}
