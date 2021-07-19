  unsigned short value = 0;

void setup() {
 pinMode(6, OUTPUT);


}

void loop() 
{
 value = analogRead(A0);
 analogWrite(6, value/4);
 delay (20);
}
