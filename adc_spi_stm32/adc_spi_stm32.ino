//ардуина опрашивает датчик DHT22 и предаёт в режиме слейва данные температуры и влажности
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
uint8_t raw_hum [4] = {0}; uint8_t raw_temp [4] = {0}; //4х байтные массивы для хранения данных типа float побайтно

ISR(SPI_STC_vect) 
{
noInterrupts();
unsigned char br = SPDR; //SPDR - принятый по SPI байт
unsigned char temp = 0;
//Serial.println (br);
if (br == 202) //если получена команда от мастера с кодом 0x1A
  {
    Serial.println ("yes"); 
    for (uint8_t count = 0; count < 4; count++) { //отправим массив с полученной от датчика значением температуры
    temp = SPI.transfer (raw_temp[count]);
    }
  }
interrupts();
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
/*разделим значение типа float на байты и запишем в массив*/                  
  (float&) raw_hum = value_humidity; 
  /*for (uint8_t count = 0; count < 4; count++)
  {
  Serial.print (raw_hum[count]);
  }
  Serial.println ();*/
  
  (float&) raw_temp = value_temp;
 /* for (uint8_t count = 0; count < 4; count++)
  {
    Serial.print (raw_temp[count]);
  }
  Serial.println ();*/
  
  }
  delay(5000);
}
