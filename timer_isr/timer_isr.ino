#include <avr/io.h>
#include <avr/interrupt.h>
#include <GyverTimers.h>
#define LEDPIN1 12
#define LEDPIN2 13
unsigned short count = 0;

ISR (TIMER1_COMPA_vect)

{
 digitalWrite(LEDPIN1, !digitalRead(LEDPIN1));
 Serial.println ("Timer_1\r\n");
}

ISR(TIMER0_A) 
{
 count++;
 if (count >= 500)
 {
 digitalWrite(LEDPIN2, !digitalRead(LEDPIN2));
 Serial.println ("Timer_0\r\n");
 count = 0;
 }

}

void timer1_init ()
{
TCCR1B |= (1 << WGM12); // устанавливаем режим СТС (сброс по совпадению)
TCCR1A = 0; // установить TCCR1A регистр в 0
TCCR1B = 0;
OCR1AH = 0b00001001; //записываем в регистр число для сравнения (4000000/256 = 15625)
OCR1AL = 0b00111101; 
//TCCR1B |= (1 << CS10); // Установка коэффициента деления 1024
TCCR1B |= (1 << CS12); //Установка коэффициента деления 256
TIMSK1 |= (1 << OCIE1A);//устанавливаем бит разрешения прерывания 1 счетчика по совпадению с OCR1A(H и L)
}

void setup ()
{
pinMode(LEDPIN1, OUTPUT);
pinMode(LEDPIN2, OUTPUT);
// инициализация Timer1
cli(); // отключить глобальные прерывания
timer1_init ();
Timer0.setPeriod(1000); //прерывание 1 мс
Timer0.enableISR(); // Запускаем прерывание (по умолч. канал А)
sei();  // включить глобальные прерывания

Serial.begin(57600);
Serial.println ("Timer_1_start\r\n");
}

void loop()
{}
