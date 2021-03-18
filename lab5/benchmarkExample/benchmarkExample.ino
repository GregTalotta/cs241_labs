#include "benchmark.h" //<- Dr. Lawlor's code

const int Numpins = 6;
const static char pins[Numpins] = {8, 9, 10, 11, 12, 13};

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < Numpins; ++i)
  {
    pinMode(pins[i], OUTPUT);
  }
}

// Define functions to be benchmarked.
//  These need to take int and return int.
int addInt(int v)
{
  int i = 1;
  return v + i;
}

int digitalWrite1(int v)
{
  digitalWrite(8, HIGH);
  return v;
}

int digitalWrite6(int v)
{
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  return v;
}

int digitalWrite6t(int v)
{
  for (int i = 0; i < Numpins; ++i)
  {
    digitalWrite(pins[i], HIGH);
  }
  return v;
}

int digitalWrite6P(int v)
{
  PORTB = 0b000000;
  return v;
}

int digitalRead1(int v)
{
  digitalRead(8);
  return v;
}

int digitalReadb(int v)
{
  PINB;
  return v;
}

int analogRead1(int v)
{
  analogRead(A0);
  return v;
}

int delayMic1(int v)
{
  delayMicroseconds(1);
  return v;
}

int delayMic10(int v)
{
  delayMicroseconds(10);
  return v;
}

int delay1(int v)
{
  delay(1);
  return v;
}

int ret0(int v)
{
  return 0;
}

int andInt(int v)
{
  int i = 3;
  return v & i;
}

int mullInt(int v)
{
  int i = 3;
  return v * i;
}

int divInt(int v)
{
  int i = 3;
  return v / i;
}

int serialP(int v)
{
  Serial.print((char)0);
  return v;
}

int addFloat(int v)
{
  float x = 6.2;
  x = x + v;
  return (int) x;
}

void loop()
{
  for (int i = 0; i < Numpins; ++i)
  {
    digitalWrite(pins[i], LOW);
  }
  Serial.println("Starting benchmarks...");
  // Call benchmark on our functions

  benchmark("digitalWrite1", digitalWrite1, 10000);
  benchmark("digitalWrite6", digitalWrite6, 10000);
  benchmark("digitalWrite6 table", digitalWrite6t, 10000);
  benchmark("digitalWrite6 Port", digitalWrite6P, 10000);
  benchmark("digitalRead1", digitalRead1, 10000);
  benchmark("digitalRead Port", digitalReadb, 10000);
  benchmark("analog read", analogRead1, 10000);
  benchmark("delayMicroseconds 1", delayMic1, 10000);
  benchmark("delayMicroseconds 10", delayMic10, 10000);
  benchmark("delay 1", delay1, 10000);
  benchmark("return 0", ret0, 10000);
  benchmark("andInt", andInt, 10000);
  benchmark("addInt", addInt, 10000);
  benchmark("mulInt", mullInt, 10000);
  benchmark("divInt", divInt, 10000);
  benchmark("addFloat", addFloat, 10000);
  benchmark("serialPrint", serialP, 10000);
  delay(3);
  Serial.println();
  delay(8000);
}
