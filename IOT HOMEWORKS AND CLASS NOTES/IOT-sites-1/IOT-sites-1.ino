void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input == "command1" || input == "command2") {
      Serial.println("ok");
    } 
    else if (input.startsWith("ATLEDD=")) {
      String state = input.substring(7);
      if (state.equalsIgnoreCase("ON")) {
        digitalWrite(13, HIGH); 
        delay(500); 
      } 
      else if (state.equalsIgnoreCase("OFF")) {
        digitalWrite(13, LOW); 
        delay(500); 
      }
    } 
    else if (input == "ATLEDDU") {
      for (int i = 0; i < 5; i++) { 
        digitalWrite(13, LOW);
        delay(500);           
        digitalWrite(13, HIGH); 
        delay(500);
      }
    }
  }
}
