const int driverPin = 26;
const int gatePin = 25;
const int driverButton = 21;
const int gateButton = 17;
boolean gate_on = false;

byte current_button = LOW;
byte old_button = LOW;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(driverPin, OUTPUT);
  pinMode(gatePin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(driverButton, INPUT);
  pinMode(gateButton, INPUT);
  Serial.println("program begin!");
}

void loop() {
  if (digitalRead(driverButton) == HIGH) {
    digitalWrite(driverPin, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
  } else {
    digitalWrite(driverPin, LOW);
    digitalWrite(LED_BUILTIN, LOW);
  }

  current_button = digitalRead(gateButton);
  if ((old_button == LOW)
      && (current_button == HIGH)) {
    gate_on = !gate_on;
  }
  old_button = current_button;
  if (gate_on == true) {
    Serial.print(millis());
    Serial.println("Gate activated!");
    digitalWrite(gatePin, HIGH);
  } else {
    digitalWrite(gatePin, LOW);
    Serial.print(millis());
    Serial.println("Gate off!");
  }
}
