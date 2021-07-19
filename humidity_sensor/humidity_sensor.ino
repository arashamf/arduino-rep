unsigned short sensor_pin = A0; 
unsigned short output_value ;
void setup() {
  Serial.begin(57600);
  Serial.println("Reading From the Sensor ...");
  delay(1000);

}

void loop() {
  output_value= analogRead(sensor_pin);
 // output_value = map(output_value,1023,0,0,100); //map(value, fromLow, fromHigh, toLow, toHigh)
  Serial.print("Mositure : ");
  Serial.println(output_value);
  delay(1000);

}
