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

const int nCommands = 7;
const String available_commands[nCommands] = {
    "help\n\tprints all available commands",
    "Lstr\n\tcorrups local string",
    "Gstr\n\tcorrupts glibal string",
    "Larr\n\tcorrupts local array",
    "Garr\n\tcorrupts global array",
    "AllG\n\tcorrupts all global variables",
    "All\n\tcorrupts all stack variables"};

void help()
{
  Serial.print("\n");
  for (int i = 0; i < nCommands; ++i)
  {
    Serial.print(available_commands[i] + "\n");
  }
  return;
}

void corrLstr()
{
  char *x = "hello\n";
  corruptMemory(&x, 7, 10000);
  Serial.println(x);
  return;
}

char *gstr = "gello\n";
void corrGstr()
{
  corruptMemory(&gstr, 7, 10000);
  Serial.println(gstr);
  return;
}

void corrLarr()
{
  int x[10] = {0};
  corruptMemory(&x, sizeof(x), 10000);
  for (int i = 0; i < 5; ++i)
  {
    Serial.println(x[i]);
  }
  return;
}

int gx[10] = {0};
void corrGarr()
{
  corruptMemory(&gx, sizeof(gx), 10000);
  for (int i = 0; i < 5; ++i)
  {
    Serial.println(gx[i]);
  }
  return;
}

void corrAllG()
{
  void *address = (void *)0x256;
  corruptMemory(&address, 300, 10000);
  return;
}

void corrAll()
{
  void *address = (void *)0x2000;
  corruptMemory(&address, 300, 10000);
  return;
}
void handleCommand(String command)
{
  char *ptr1;
  Serial.println("Received Command: " + command);
  if (command == "help")
  {
    help();
  }
  if (command == "Lstr")
  {
    corrLstr();
  }
  if (command == "Gstr")
  {
    corrGstr();
  }
  if (command == "Larr")
  {
    corrLarr();
  }
  if (command == "Garr")
  {
    corrGarr();
  }
  if (command == "AllG")
  {
    corrLarr();
  }
  if (command == "All")
  {
    corrLarr();
  }
  return;
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Enter \"help\" for commands");
  randomSeed(1234);
}

String buffer;
void loop()
{
  while (Serial.available() > 0)
  {
    int c = Serial.read();
    if (c < 0)
      break;
    if (c == '\n')
    { // newline, check for a valid command
      handleCommand(buffer);
      buffer = "";
    }
    else if (c != '\r')
    { // normal non-control char, just add it to the string
      buffer += (char)c;
    }
  }
  // … do normal work here: blink LEDs, etc
}
