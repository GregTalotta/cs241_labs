// Greg Talotta lab 10
int comPin = 12;
int ossPin = 8;
void setup()
{
  Serial.begin(9600);
  pinMode(comPin, OUTPUT);
  digitalWrite(comPin, HIGH);
  pinMode(ossPin, INPUT);
}


unsigned long duration = 0;
void loop()
{
    duration = pulseIn(ossPin, LOW);
    Serial.println(duration);
}
