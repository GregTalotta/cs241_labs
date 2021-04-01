// Greg Talotta lab 10
int relayPin = 12;
void setup()
{
  Serial.begin(9600);
  pinMode(relayPin,OUTPUT);
  digitalWrite(relayPin,LOW);
}

bool swap = true;
void loop()
{
  if(swap){
    digitalWrite(relayPin,HIGH);
    swap = !swap;
  }else{
    //digitalWrite(relayPin,LOW);
    swap = !swap;
  }
  delay(300);
}
