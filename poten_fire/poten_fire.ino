unsigned short value = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(57600);
Serial.println("program start\r\n");
}

void loop() {
 
value = analogRead(A7);
//(30);
if (value < 204)
  {
  digitalWrite(A0, HIGH);  
  digitalWrite(A4, LOW);
  }
if ((value > 204) && (value < 408))
  {
  digitalWrite(A1, HIGH);
  digitalWrite(A0, LOW);  
  }
if ((value > 408) && (value < 612))
  {
  digitalWrite(A2, HIGH);  
  digitalWrite(A1, LOW);
  }
if ((value > 612) && (value < 816))
  {
  digitalWrite(A3, HIGH); 
  digitalWrite(A2, LOW); 
  }
if ((value > 816) && (value < 1023))
  {
  digitalWrite(A4, HIGH); 
  digitalWrite(A3, LOW); 
  }  
//Serial.println(value);
delay(30); //задержка в мс


}
