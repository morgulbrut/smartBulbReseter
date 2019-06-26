// include the GSM library
#include <MKRGSM.h>

#include "arduino_secrets.h"
// Please enter your sensitive data in the Secret tab or arduino_secrets.h
// #define SECRET_PINNUMBER  "1234"
const char PINNUMBER[] = SECRET_PINNUMBER;

// initialize the library instances
GSM gsmAccess;
GSM_SMS sms;
GSMVoiceCall vcs;

// Array to hold the number a SMS is retreived from
char senderNumber[20];

/*
   Neopixel stuff
*/

#include <Adafruit_NeoPixel.h>

const int LED_PIN = 5;
const int NO_PIXEL = 16;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NO_PIXEL, LED_PIN, NEO_GRB + NEO_KHZ400);


/*
   Relay stuff
*/
#include <timer.h>

auto timer = timer_create_default();

const int REL1_PIN = 4;
const int REL2_PIN = 7;
const int REL1_PULSE = 2500;


void parse_SMS(String keyword) {
  keyword.toLowerCase();
  if (keyword.substring(0) == "ge_pre_2.7") {
    colorWipe(strip.Color(255, 0, 0), 50);
    resetGEpre27();
    colorWipe(strip.Color(0, 0, 0), 50);
  }
  if (keyword.substring(0) == "ge_post_2.8") {
    colorWipe(strip.Color(255, 128, 0), 50);
    resetGEpost28();
    colorWipe(strip.Color(0, 0, 0), 50);
  }
}


void setup() {
  strip.begin();
  strip.show();
  pinMode(REL1_PIN, OUTPUT);
  pinMode(REL2_PIN, OUTPUT);
  digitalWrite(REL1_PIN, HIGH);
  digitalWrite(REL2_PIN, HIGH);

  // initialize serial communications and wait for port to open:
  colorWipe(strip.Color(255, 0, 255), 50);
  Serial.begin(9600);


  Serial.println("SMS Messages Receiver");

  // connection state
  bool connected = false;

  // Start GSM connection
  while (!connected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
      connected = true;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("GSM initialized");
  Serial.println("Waiting for messages");
  colorWipe(strip.Color(0, 0, 0), 50);
}

void loop() {
  int c;

  switch (vcs.getvoiceCallStatus()) {
    case IDLE_CALL: // Nothing is happening
      // If there are any SMSs available()
      if (sms.available()) {
        Serial.println("Message received from:");

        // Get remote number
        sms.remoteNumber(senderNumber, 20);
        Serial.println(senderNumber);

        // An example of message disposal
        // Any messages starting with # should be discarded
        if (sms.peek() == '#') {
          Serial.println("Discarded SMS");
          sms.flush();
        }

        // Read message bytes and print them
        String msg = "";
        while ((c = sms.read()) != -1) {
          msg += ((char)c);
        }
        parse_SMS(msg);
        Serial.println(msg);

        Serial.println("\nEND OF MESSAGE");

        // Delete message from modem memory
        sms.flush();
        Serial.println("MESSAGE DELETED");
      }
      break;
  }

  timer.tick();
}
