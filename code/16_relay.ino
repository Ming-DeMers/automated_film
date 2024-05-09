const int controlPin[16] = { 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37 };
const int buttonPin = 53;
const int ledPin = 13;
const int triggerType = LOW;
int tmpStat = 1;

void setup() {
  for (int i = 0; i < 16; i++) {
    pinMode(controlPin[i], OUTPUT);  // set pin as output
    if (triggerType == LOW) {
      digitalWrite(controlPin[i], HIGH);  // set initial state OFF for low trigger relay
    } else {
      digitalWrite(controlPin[i], LOW);  // set initial state OFF for high trigger relay
    }
  }
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  relayTestSequence();
  Serial.begin(9600);  // initialize serial monitor with 9600 baud
}

void channelControl(int relayChannel, int action, int t = 10) {
  int state = LOW;
  String statTXT = " ON";
  if (triggerType == LOW) {
    if (action == 0)  // if OFF requested
    {
      state = HIGH;
      statTXT = " OFF";
    }
    digitalWrite(controlPin[relayChannel], state);
    if (t > 0) {
      delay(t);
    }
    Serial.print("Channel: ");
    Serial.print(relayChannel);
    Serial.print(statTXT);
    Serial.print(" - ");
    Serial.println(t);
  } else {
    if (action == 1)  // if ON requested
    {
      state = HIGH;
    } else {
      statTXT = " OFF";
    }
    digitalWrite(controlPin[relayChannel], state);
    if (t > 0) {
      delay(t);
    }
    Serial.print("Channel: ");
    Serial.print(relayChannel);
    Serial.print(statTXT);
    Serial.print(" - ");
    Serial.println(t);
  }
}

void pumpForward(int t=10) {
  channelControl(0, 1, t);
  channelControl(0, 0, 10);
}

void pumpBack(int t=10) {
  channelControl(1, 1, t);
  channelControl(1, 0, 10);
}

void loop() {
  if (Serial.available() > 0) {
    int relay = (int)Serial.read() - 48;
    if (relay == 42) {
      for (int i = 0; i < 16; i++) {
        channelControl(i, 0);  // turn each relay off for 200ms
      }
    } else {
    channelControl(relay, 1);
    delay(10);
    }
  } 

  while (digitalRead(buttonPin) == HIGH) {
    digitalWrite(ledPin, HIGH);
    pumpForward();
  }
}




// a testing method to test all 16 relays
void relayTestSequence() {
  for (int i = 0; i < 16; i++) {
    channelControl(i, tmpStat, 100);  // turn each relay ON for 200ms
  }
  if (tmpStat) {
    tmpStat = 0;
  } else {
    tmpStat = 1;
  }

  for (int i = 0; i < 16; i++) {
    channelControl(i, tmpStat, 0);  // turn each relay ON for 200ms
  }
  if (tmpStat) {
    tmpStat = 0;
  } else {
    tmpStat = 1;
  }
  Serial.println("Test complete");
}