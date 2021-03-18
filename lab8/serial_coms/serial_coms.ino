

void setup()
{
    Serial.begin(9600);
    pinMode(9, INPUT_PULLUP);
    pinMode(7, OUTPUT);
}

void loop()
{
    int button=digitalRead(9);
    if(button==0){
      Serial.print("PRESSED!\n");
      digitalWrite(7, HIGH);
      delay(1000); 
    }
}
