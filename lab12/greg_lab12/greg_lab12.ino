//greg lab 12
int fetPin = 3;

void setup()
{
  Serial.begin(9600);
  pinMode(fetPin, OUTPUT);
}
float V = 0.0;
void loop()
{
  if (V < 3.7)
  {
    digitalWrite(fetPin, HIGH);
  }
  else
  {
    digitalWrite(fetPin, LOW);
  }
  int rawVoltage = analogRead(A0);
  V = rawVoltage * (5.0 / 1023);
  Serial.println(V);
}
