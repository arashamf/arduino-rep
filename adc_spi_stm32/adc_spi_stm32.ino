#include <SPI.h>

unsigned short sensor_pin = A0; 
unsigned short output_value [5]; //массив со значениями АЦП
uint8_t count = 0;

ISR(SPI_STC_vect) 
{
unsigned char br = SPDR;
if (br == 0xCA)
  {
    SPI.transfer (output_value [count]);
  }
}

void setup() {
  Serial.begin(57600);
  Serial.println("Reading From the Sensor ...");
  //  Инициализируем SPI при SS в режиме INPUT (получаем slave режим) и вручную выставляем правильные направления пинов
  SPI.begin();
  SPI.beginTransaction (SPISettings()); //SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0))
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);
  SPI.attachInterrupt();  // Включаем прерывания
  delay(500);
}

void loop() {
  for (count = 0; count < 5; count++)
    {
    output_value [count] = analogRead(sensor_pin);
 // output_value = map(output_value,1023,0,0,100); //map(value, fromLow, fromHigh, toLow, toHigh)
    Serial.print("VALUE : ");
    Serial.println(output_value [count]);
    delay(500); 
    }
 
}
