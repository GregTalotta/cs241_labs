// Greg Talotta lab 9

/*
 Apply bit errors to this piece of memory.
 "bitErrorRate" is the number of flipped bits per million* bits:
   bitErrorRate==0 does nothing.
   bitErrorRate==1000 flips about 1/1000 bits.
   bitErrorRate==1000000 flips basically every bit (inverts the data).
 Calls random(), use randomSeed() if you need repeatable numbers.
 *: Arduino random(max) uses mod, which works very poorly in the long run.
    We use the raw binary random numbers, which requires a power of 2,
    so this is relative to binary million (1048576) not decimal million.
 */

void corruptMemory(void *startPointer, int nBytes, long bitErrorRate)
{
  const unsigned long megaMask = 0xFFFFF; // == 20 set bits, approx 1 million
  unsigned char *start = (unsigned char *)startPointer;
  for (int i = 0; i < nBytes; i++)
    for (unsigned int bit = 0; bit < 8; bit++)
      if ((random() & megaMask) < bitErrorRate)
        start[i] ^= (1 << bit); // flip this bit
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int x=0;
  corruptMemory(&x,sizeof(x),10000);
  if(x != 0){
    Serial.print("X is: ");
    Serial.println(x);
  }
  delay(300);
}
