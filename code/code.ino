const int controlPin[16] = { 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37 };
const int buttonPin = 18;
const int ledPin = 13;
int tmpStat = 1;

void setup() {
  for (int i = 0; i < 16; i++) {
    pinMode(controlPin[i], OUTPUT);
  }
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  relayTestSequence();
  Serial.begin(9600);  // initialize serial monitor with 9600 baud
}

// activate any specified channel
// relayChannel: the channel number
// action: 0 for off, 1 for on
// t: duration in milliseconds
void channelControl(int relayChannel, int action, int t = 0) {
  Serial.print("Channel: ");
  Serial.print(relayChannel);
  Serial.print(" Action: ");
  Serial.println(action);
  if (action == 0)  // if OFF requested
  {
    digitalWrite(controlPin[relayChannel], HIGH);
  } else {
    digitalWrite(controlPin[relayChannel], LOW);
  }
  delay(t);
}

// pump water forward, from a silo to the dev tank
void pumpAForward(int t = NULL) {
  channelControl(0, 1, t);
  channelControl(0, 0, t);
}

// pump water back, from dev tank to a silo
void pumpABack(int t = NULL) {
  channelControl(1, 1);
  channelControl(1, 0);
}

// pump water forward, from a silo to the dev tank
void pumpBForward(int t = NULL) {
  channelControl(14, 1, t);
  channelControl(14, 0, 10);
}

// pump water back, from dev tank to a silo
void pumpBBack(int t = NULL) {
  channelControl(15, 1, t);
  channelControl(15, 0, 10);
}

void pump1Forward(int t = NULL) {
  channelControl(2, 1);
  channelControl(3, 1);
  channelControl(0, 1);
  channelControl(14, 1);
  delay(t);
  allRelayOff();
}

void pump1Back(int t = NULL) {
  channelControl(2, 1);
  channelControl(3, 1);
  channelControl(1, 1);
  channelControl(15,1);
  delay(t);
  allRelayOff();
}

void loop() {
  while (digitalRead(buttonPin) == LOW) {
    if (Serial.available() > 0) {
      int inInt = (int)Serial.read() - 48;
      switch (inInt) {
        case 1:
          pump1Forward(10000);
          if (digitalRead(buttonPin) == HIGH) { break; }
          break;
        case 2:
          pump1Back(10000);
          if (digitalRead(buttonPin) == HIGH) { break; }
          break;
      }
    }
  }
  digitalWrite(ledPin, HIGH);

  // current_button = digitalRead(buttonPin);
  // if ((old_button == LOW)
  //     && (current_button == HIGH)) {
  //   buttonOn = !buttonOn;
  //   delay(100);
  // }
  // old_button = current_button;
  // if (buttonOn == true) {
  //   pumpForward(0);
  //   digitalWrite(ledPin, HIGH);
  // } else {
  //   digitalWrite(ledPin, LOW);
  // }
}




// a testing method to test all 16 relays
void relayTestSequence() {
  for (int i = 0; i < 16; i++) {
    channelControl(i, 1, 50);  // turn each relay ON for 200ms
    delay(50);
  }
  delay(50);

  allRelayOff();
}

void allRelayOff() {
  for (int i = 0; i < 16; i++) {
    channelControl(i, 0);  // turn each relay ON for 200ms
  }
}