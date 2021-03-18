void handleCommand(String cmd) {
  Serial.println("> " + cmd);
  if (cmd == "help") {
    Serial.println("Commands:\nhelp  Print this help text\nok  Print OK");
  }
  else if (cmd == "ok") {
    Serial.println("OK");
  }
  else if (cmd[0] == 'A' && cmd.length() == 2) {
    int digit = cmd[1] - '0';
    if (digit >= 0 && digit <= 5) {
      int v = analogRead(digit + A0);
      float realV = 5.0 * v / 1023.0;
      Serial.println(v);
      Serial.println(realV);
    }
    else {
      Serial.println("Unrecognized analog pin: " + cmd);
    }
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
