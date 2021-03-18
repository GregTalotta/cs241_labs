// Greg Talotta lab 8
const int nCommands = 11;
const String available_commands[nCommands] = {
    "help\n\tprints all available commands",
    "ok\n\tprints OK",
    "A<digit>\n\treads the voltage on that anolog pin",
    "on\n\tturn the pin 13 debug pin on",
    "off\n\tturn the pin 13 debug pin off",
    "xs\n\tprint x 10000 times",
    "baud\n\tChange the serial baud rate to 19200, and print \"are you reading this?\"",
    "grüning\n\ttest a unicode character",
    "fill ram\n\tallocates 512 bytes of ram and prints the ptr as long",
    "ptr null\n\tprints what is stored at NULL",
    "array\n\tuses new to create an array size 3, then prints the 100th element"};

void help()
{
  Serial.print("\n");
  for (int i = 0; i < nCommands; ++i)
  {
    Serial.print(available_commands[i] + "\n");
  }
  return;
}

void ok()
{
  Serial.println("OK");
  return;
}

void voltageRead(int aPin)
{
  int v = analogRead(aPin); // raw 0-1023 analog-to-digital reading
  //float V = 5.0 * v / 1023.0; // scale to float volts
  Serial.print("Voltage is ");
  Serial.println(v); // print voltage (in volts)
}

int parsePin(char pos)
{
  int i = (pos - '0') + A0;
  if ((i < A0) || (i > A5))
  {
    i = -1;
  }
  return i;
}

void handleCommand(String command)
{
  char *ptr1;
  Serial.println("Received Command: " + command);
  if (command == "help")
  {
    help();
  }
  if (command == "ok")
  {
    ok();
  }
  if (command[0] == 'A')
  {
    int pin = parsePin(command[1]);
    if (pin != -1)
    {
      voltageRead(pin);
    }
  }
  if (command == "off")
  {
    digitalWrite(13, LOW);
  }
  if (command == "on")
  {
    digitalWrite(13, HIGH);
  }
  if (command == "xs")
  {
    for (int i = 0; i < 10000; ++i)
    {
      Serial.print("x");
    }
  }
  if (command == "grüning")
  {
    for (int i = 0; i < command.length(); ++i)
    {
      Serial.print(command[i], HEX);
    }
    Serial.println();
  }
  if (command == "ptr null")
  {
    int *ptr = NULL;
    Serial.println(*ptr);
  }
  if (command == "fill ram")
  {
    ptr1 = new char[512];
    Serial.println((long)ptr1);
  }
  if (command == "array")
  {
    char *ptr2 = new char[3];
    Serial.println(ptr2[100]);
    delete (ptr2);
  }
  if (command == "baud")
  {
    Serial.end();
    Serial.begin(19200);
    Serial.println("Are you reading this?");
  }
  return;
}

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  Serial.println("Command demo!");
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
