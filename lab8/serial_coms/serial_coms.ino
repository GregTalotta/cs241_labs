// Greg Talotta lab 8
const int nCommands = 2;
const String available_commands[nCommands] = {
  "help\n\tprints all available commands",
  "ok\n\tprints OK"
};

void help(){
  Serial.print("\n");
  for(int i = 0; i < nCommands; ++i){
    Serial.print(available_commands[i]+"\n");
  }
  return;
}

void ok(){
  Serial.print("OK");
  return;
}

void handleCommand(String command){
  Serial.print("Received Command: " + command+ "\n");
  if(command == "help"){
    help();
  }
  if(command == "ok"){
    ok();
  }
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
