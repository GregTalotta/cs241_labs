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

void corruptMemory(void *startPointer,int nBytes,long bitErrorRate)
{ 
  const unsigned long megaMask=0xFFFFF; // == 20 set bits, approx 1 million
  unsigned char *start=(unsigned char *)startPointer;
  for (int i=0;i<nBytes;i++)
    for (unsigned int bit=0;bit<8;bit++)
      if ((random()&megaMask)<bitErrorRate)
        start[i] ^= (1<<bit); // flip this bit
}

char *Gstr= "gello\n";
const int RATE = 10000;
int Garr[10]={0};

void handleCommand(String cmd) {
  Serial.println("> " + cmd);
  if (cmd == "lstr") {
    char *Lstr= "hello\n";
    corruptMemory(Lstr, 7, RATE);
    Serial.print(Lstr);
  }
  else if (cmd == "gstr") {
    corruptMemory(Gstr, 7, RATE);
    Serial.print(Gstr);
  }
  else if (cmd == "larr") {
    int Larr[10]={0};
    corruptMemory(Larr, sizeof(Larr), RATE);
    for (int i = 0; i < 10; i++) {
      Serial.println(Larr[i]);
    }
  }
  else if (cmd == "garr") {
    corruptMemory(Garr, sizeof(Garr), RATE);
    for (int i = 0; i < 10; i++) {
      Serial.println(Garr[i]);
    }
  }
  else if (cmd == "allg") {
    corruptMemory(256, 300, RATE);
  }
  else if (cmd == "alls") {
    corruptMemory(2000, 300, RATE);
  }
  else {
    Serial.println("Unrecognized command: " + cmd);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to Lab 09.");
  pinMode(13, OUTPUT);
  randomSeed(1234);
}

String buffer;

void loop() {
  while (Serial.available() > 0) {
    int c = Serial.read();
    if (c < 0) break;
    if (c == '\n') {
      handleCommand(buffer);
      buffer = "";
    }
    else if (c != '\r') {
      buffer += (char)c;
    }
  }
}
