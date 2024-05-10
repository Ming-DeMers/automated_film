// // const int controlPin[16] = { 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37 };
// // const int buttonPin = 18;
// // const int ledPin = 13;
// // const int triggerType = LOW;
// // int tmpStat = 1;

// // void setup() {
// //   for (int i = 0; i < 16; i++) {
// //     pinMode(controlPin[i], OUTPUT);  // set pin as output
// //     if (triggerType == LOW) {
// //       digitalWrite(controlPin[i], HIGH);  // set initial state OFF for low trigger relay
// //     } else {
// //       digitalWrite(controlPin[i], LOW);  // set initial state OFF for high trigger relay
// //     }
// //   }
// //   pinMode(ledPin, OUTPUT);
// //   pinMode(buttonPin, INPUT);
// //   relayTestSequence();
// //   Serial.begin(9600);  // initialize serial monitor with 9600 baud
// // }

// // activate any specified channel
// // relayChannel: the channel number
// // action: 0 for off, 1 for on
// // t: duration in milliseconds
// void channelControl(int relayChannel, int action, int t = 10) {
//   int state = LOW;
//   String statTXT = " ON";
//   if (triggerType == LOW) {
//     if (action == 0)  // if OFF requested
//     {
//       state = HIGH;
//       statTXT = " OFF";
//     }
//     digitalWrite(controlPin[relayChannel], state);
//     if (t > 0) {
//       delay(t);
//     }
//     Serial.print("Channel: ");
//     Serial.print(relayChannel);
//     Serial.print(statTXT);
//     Serial.print(" - ");
//     Serial.println(t);
//   } else {
//     if (action == 1)  // if ON requested
//     {
//       state = HIGH;
//     } else {
//       statTXT = " OFF";
//     }
//     digitalWrite(controlPin[relayChannel], state);
//     if (t > 0) {
//       delay(t);
//     }
//     Serial.print("Channel: ");
//     Serial.print(relayChannel);
//     Serial.print(statTXT);
//     Serial.print(" - ");
//     Serial.println(t);
//   }
// }

// // pump water forward, from a silo to the dev tank
// void pumpForward(int t = 10) {
//   channelControl(0, 1, t);
//   channelControl(0, 0, 10);
// }

// // pump water back, from dev tank to a silo
// void pumpBack(int t = 10) {
//   channelControl(1, 1, t);
//   channelControl(1, 0, 10);
// }

// void pump1Forward(int t = 10) {
//   channelControl(2, t);
//   channelControl(3, t);
//   pumpForward(t);
// }

// void pump1Back(int t = 10) {
//   channelControl(2, t);
//   channelControl(3, t);
//   pumpBack(t);
// }

// // a testing method to test all 16 relays
// void relayTestSequence() {
//   for (int i = 0; i < 16; i++) {
//     channelControl(i, tmpStat, 50);  // turn each relay ON for 200ms
//   }
//   if (tmpStat) {
//     tmpStat = 0;
//   } else {
//     tmpStat = 1;
//   }

//   for (int i = 0; i < 16; i++) {
//     channelControl(i, tmpStat, 10);  // turn each relay ON for 200ms
//   }
//   if (tmpStat) {
//     tmpStat = 0;
//   } else {
//     tmpStat = 1;
//   }
//   Serial.println("Test complete");
// }