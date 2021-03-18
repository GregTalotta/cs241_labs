void handleCommand(String command){
  Serial.print("Received Command: " + command);

  return;
}

void setup()
{
  Serial.begin(9600);
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
