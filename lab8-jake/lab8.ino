void handleCommand(String cmd) {
  Serial.println("> " + cmd);
  if (cmd == "help") {
    Serial.println("Commands:\nhelp  Print this help text\nok  Print OK");
  }
  else if (cmd == "ok") {
    Serial.println("OK");
  }
  else {
    Serial.println("Unrecognized command: " + cmd);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to Lab 08.");
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
