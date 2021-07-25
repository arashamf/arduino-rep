#include <SPI.h>
#include <DHT.h>

#define DHTPIN 2     // номер пина, к которому подсоединен датчик
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);     // Инициализация сенсора DHT

unsigned short sensor_pin = A0; 
float value_humidity = 0; //значение влажности
float value_temp = 0; //значение температуры
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
  
  SPI.begin(); //  Инициализируем SPI при SS в режиме INPUT (получаем slave режим) и вручную выставляем правильные направления пинов
  SPI.beginTransaction (SPISettings()); //SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0))
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);
  SPI.attachInterrupt();  // Включаем прерывания

  dht.begin();
  
  delay(500);
}

void loop() {
/*  for (count = 0; count < 5; count++)
    {
    output_value [count] = analogRead(sensor_pin);
 // output_value = map(output_value,1023,0,0,100); //map(value, fromLow, fromHigh, toLow, toHigh)
    Serial.print("VALUE : ");
    Serial.println(output_value [count]);
    delay(500); 
    }*/
value_humidity = dht.readHumidity();    // cчитывание влажности
value_temp = dht.readTemperature();     // cчитывание температуры

// проверка NaN (вывод цифровых значений) 
if (isnan(value_humidity) || isnan(value_temp)) 
  {
  Serial.println("Data error!");
  }
else
  {
  Serial.print ("Humidity: ");
  Serial.print (value_humidity);
  Serial.print ("%\t");
  Serial.print ("Temperature: ");
  Serial.print (value_temp);
  Serial.println (" *C");
  delay(1000);
  }
}
