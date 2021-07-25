#include <LowPower.h>
#include <TFT.h>  
#include <SPI.h>

#define CS   10 //чип селект
#define DC   9 //
#define RST  8 // сброс дисплея, активный низкий уровень

#define SensorPin A0 //аналоговый вход для датчика
#define SensorPower 2 //выход 2 - питание датчика

#define LED 5 //ШИМ-выход на светодиод

TFT myScreen = TFT (CS, DC, RST);
uint8_t count = 0;
char buffer [20];
unsigned short value = 0;

void setup() 
{
pinMode(SensorPower, OUTPUT);
digitalWrite(SensorPower, LOW); // Изначально оставляем датчик выключенным
pinMode(LED, OUTPUT);

Serial.begin(19200);
myScreen.begin();  
myScreen.background(255, 128, 255);  // очищаем экран, заливая его цветом
myScreen.stroke(255, 255, 255); //Функция stroke() изменяет цвет текста
myScreen.setTextSize(2); // задаем размер текста 
myScreen.text("sensor\n", 1, 0); // передвигаем курсор в левый верхний угол, чтобы начать писать оттуда
myScreen.text("start\n", 1, 20);
Serial.println("sensor_start\n"); 
delay (500);
}

void loop() 
{
   myScreen.background(255, 128, 255);  // очищаем экран
   sprintf (buffer, "value=%d\n", value = readSensor());
   myScreen.text(buffer, 5, 20);

   analogWrite(LED, value/4); //зажигаем светодиод пропорционально влажности
   Serial.print("get_value\n");
   delay (1000);
   analogWrite(LED, 0);    
   while ((count++) < 3) //цикл сна 8*count
    {
    LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF); //засыпаем на 8 с
     }
    count = 0;
    Serial.print("arduino_wake_up\n");
    delay (500);
}

// Данная функция возвращает аналоговый результат измерений датчика влажности почвы
unsigned short readSensor() 
{
  digitalWrite(SensorPower, HIGH);  // Включить датчик
  delay(50);                        // Дать время питанию датчика установиться
  int val = analogRead(SensorPin);  // Прочитать аналоговое значение от датчика
  digitalWrite(SensorPower, LOW);   // Выключить датчик
  return val;                       // Вернуть аналоговое значение влажности
}
