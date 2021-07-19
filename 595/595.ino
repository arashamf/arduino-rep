
int latchPin = 8; //Пин подключен к ST_CP входу 74HC595
int clockPin = 12; //Пин подключен к SH_CP входу 74HC595
int dataPin = 11; //Пин подключен к DS входу 74HC595
unsigned char digit [15] = {1,2,4,8,16,32,64,128,64,32,16,8,4,2,1};

void setup() 
{

  Serial.begin(57600);
  Serial.println("start");
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
for (short numberToDisplay = 0; numberToDisplay < 8; numberToDisplay++) 
  {
    digitalWrite(latchPin, LOW); // устанавливаем синхронизацию "защелки" на LOW
    shiftOut(dataPin, clockPin, MSBFIRST, digit [numberToDisplay]);   // передаем последовательно на dataPin
    shiftOut(dataPin, clockPin, MSBFIRST, 0x0);   // сдвигаем регистр
    digitalWrite(latchPin, HIGH);   //"защелкиваем" регистр, тем самым устанавливая значения на выходах
    Serial.println(numberToDisplay);
    delay(500);
  }
  for (short numberToDisplay = 0; numberToDisplay < 15; numberToDisplay++) 
  {
    digitalWrite(latchPin, LOW); // устанавливаем синхронизацию "защелки" на LOW
    shiftOut(dataPin, clockPin, MSBFIRST, 0x0);   // сдвигаем регистр
    shiftOut(dataPin, clockPin, MSBFIRST, digit [numberToDisplay]);   // передаем последовательно на dataPin
    digitalWrite(latchPin, HIGH);   //"защелкиваем" регистр, тем самым устанавливая значения на выходах
    Serial.println(numberToDisplay);
    delay(500);
  }
  for (short numberToDisplay = 7; numberToDisplay > 0; numberToDisplay--) 
  {
    digitalWrite(latchPin, LOW); // устанавливаем синхронизацию "защелки" на LOW
    shiftOut(dataPin, clockPin, MSBFIRST, digit [numberToDisplay]);   // передаем последовательно на dataPin
    shiftOut(dataPin, clockPin, MSBFIRST, 0x0);   // сдвигаем регистр
    digitalWrite(latchPin, HIGH);   //"защелкиваем" регистр, тем самым устанавливая значения на выходах
    Serial.println(numberToDisplay);
    delay(500);
  }
}
