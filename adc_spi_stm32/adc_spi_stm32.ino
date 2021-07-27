#include <SPI.h>
#include <DHT.h>

#define DHTPIN 2     // номер пина, к которому подсоединен датчик
#define DHTTYPE DHT22   // DHT 22  (AM2302)

#define MOSI 11 
#define MISO 12 
#define SCK  13
#define SS 10

DHT dht(DHTPIN, DHTTYPE);     // Инициализация сенсора DHT

float value_humidity = 0; //значение влажности
float value_temp = 0; //значение температуры
unsigned short output_value [5]; //массив со значениями АЦП

ISR(SPI_STC_vect) 
{
unsigned char br = SPDR; //SPDR - принятый по SPI байт
(void) SPDR;
Serial.println (br);
if (br == 0xCA)
  {
    SPI.transfer (0xAB);
  }
  else
  {
    SPI.transfer (0x55);
  } 
}

void setup() {
  Serial.begin(57600);
//  Serial.println("I am Master");
  Serial.println("Reading From the Sensor ...");
  
 // digitalWrite(SS, HIGH);
  SPI.begin(); //  Инициализируем SPI при SS в режиме INPUT (slave режим) и вручную выставляем направления пинов
  SPI.beginTransaction (SPISettings (6000000, MSBFIRST, SPI_MODE0)); //6 МГц, передача данных идёт, начиная с MSB, CPOL=0, CPHA=0
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);
  SPI.attachInterrupt();  // Включаем прерывания

  dht.begin();
  
  delay(500);
}

void loop() {
value_humidity = dht.readHumidity();    // cчитывание влажности
value_temp = dht.readTemperature();     // cчитывание температуры

if (isnan(value_humidity) || isnan(value_temp)) // проверка NaN (вывод цифровых значений) 
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
  }
  delay(2000);
}
