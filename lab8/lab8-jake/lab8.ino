char * ptr;

void handleCommand(String cmd) {
  Serial.println("> " + cmd);
  if (cmd == "help") {
    Serial.println("Commands: help, ok, on, off, xs, baud, grüning, fill ram, ptr null, array");
  }
  else if (cmd == "ok") {
    Serial.println("OK");
  }
  else if (cmd == "on") {
    digitalWrite(13, HIGH);
  }
  else if (cmd == "off") {
    digitalWrite(13, LOW);
  }
  else if (cmd == "xs") {
    for (int i = 0; i < 10000; i++) {
      Serial.print("x");
    }
  }
  else if (cmd == "baud") {
    Serial.end();
    Serial.begin(19200);
    Serial.println("Are you reading this?");
  }
  else if (cmd == "grüning") {
    for (int i = 0; i < cmd.length(); ++i) {
      Serial.println(cmd[i], HEX);
    }
  }
  else if (cmd == "fill ram") {
    ptr = new char[512];
    Serial.println((long)ptr);
  }
  else if (cmd == "ptr null") {
    int * null_ptr = NULL;
    Serial.println(*null_ptr);
  }
  else if (cmd == "array") {
    char * arr = new char[3];
    Serial.println(arr[100]);
    delete (arr);
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
  pinMode(13, OUTPUT);
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
