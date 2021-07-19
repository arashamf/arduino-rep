
  unsigned short value = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(57600);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
}


void loop() {
 value = analogRead(A0);
if (value <= 204)
  {
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  }
 if ((value <= 408) && (value > 204))
  {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  } 
 if ((value <= 612) && (value > 408))
  {
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  } 
 if ((value <= 816) && (value > 612))
  {
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  } 
 if ((value <= 1023) && (value > 816))
  {
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
  } 
//  Serial.println (value);
  delay(50); //задержка в мс
}
