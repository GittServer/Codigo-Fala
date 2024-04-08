// FALA AS FRASES DOS CODIGOS HEXA.

/* Including libraries  */
#include <Arduino.h>
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2SNoDAC.h"
#include "audiodata.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
WiFiClient client;
ESP8266WebServer server(80); /* defining server port */

/* AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out; */

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define min_pulse_width 102   /* Defining minimum pulsewidth */
#define max_pulse_width 512   /* Defining maximum pulsewidth */
#define frequency 50   /* Defining frequency as 50 Hz */

const char* ssid = "Your SSID"; /* Your SSID */
const char* password = "Your Password"; /* Your Password */

String  data = "";
Servo headservo;

void setup()
{
  Serial.begin(115200);
  Serial.println("GPIO test!");

  pwm.begin();
  pwm.setPWMFreq(frequency);
  delay(5000);
  headservo.attach(0);/* Pin D3 */
  initial_position();

  /* Connecting to WiFi */
  connectToWiFi();

  server.on("/", handleRequest);
  server.onNotFound(handleRequest);

  /* Starting Server */
  server.begin();
  Serial.println("Server started");

}

void loop() {
  Serial.println("FALANDO 1 ... hi");
  say_hi();
  delay(2000);
  Serial.println("FALANDO 2 ... bye");
  say_bye();
  delay(2000);

  server.handleClient();
  data = server.arg("data");

  if (data != "") {

    if (data.equalsIgnoreCase("hi")) {
      say_hi();
    }
    if (data.equalsIgnoreCase("what is your name") || data.equalsIgnoreCase("your name")) {
      my_name_hash();
    }
    if (data.equalsIgnoreCase("nice to meet you") || data.equalsIgnoreCase("glad to meet you")) {
      nice_to_meet_you_too();
    }
    if (data.equalsIgnoreCase("introduce yourself") || data.equalsIgnoreCase("what are you")) {
      i_am_humanoid_robot();
    }
    if (data.equalsIgnoreCase("you are amazing") || data.equalsIgnoreCase("you look amazing")) {
      thank_you();
    }
    if (data.equalsIgnoreCase("are you happy being a robot") || data.equalsIgnoreCase("do you hate mathematics")) {
      say_yes();
    }
    if (data.equalsIgnoreCase("do you love me") || data.equalsIgnoreCase("tell me your secrets")) {
      say_no();
    }
    if (data.equalsIgnoreCase("tell viewers to subscribe") || data.equalsIgnoreCase("tell them to subscribe")) {
      say_subscribe();
    }
    if (data.equalsIgnoreCase("bye")) {
      say_bye();
    }
  }
  data = "";
}

/* Reuest and resonse handling */
void handleRequest() {
  if ( server.hasArg("data") ) {
    Serial.println(server.arg("Key"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}

void connectToWiFi() {
  delay(3000);
  WiFi.disconnect();
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(500);
    Serial.print("...");
  }
  Serial.println("Connected");
  Serial.println("Local IP is : ");
  Serial.print((WiFi.localIP().toString()));
  Serial.println("\n");
  delay(5000);
}

void setServo(int servo, int angle) {
  int pulselength;
  pulselength  = map(angle, 0, 180, min_pulse_width, max_pulse_width); /* Converting degree of rotation to pulse length */
  pwm.setPWM(servo, 0, pulselength); /* Passing pulse length */
}

/******************** initial position ********************/
void initial_position() {
  headservo.write(90);
  setServo(8, 0);
  setServo(9, 0);
  setServo(10, 20);
  setServo(11, 90);
  setServo(12, 150);
  setServo(13, 30);
  setServo(14, 30);
  setServo(15, 90);

  setServo(0, 180);
  setServo(1, 180);
  setServo(2, 160);
  setServo(3, 90);
  setServo(4, 30);
  setServo(5, 150);
  setServo(6, 150);
  setServo(7, 90);
}
/******************** say hi ********************/
void say_hi() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( hi, sizeof(hi) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  for (int i = 0; i <= 180; i++) {
    setServo(8, 0 + i);
    if (i <= 90) {
      setServo(9, 0 + i);
    }
    if (i <= 40) {
      setServo(10, 20 + i);
    }
    delay(10);
  }
  for (int i = 1; i <= 1; i++) {
    for (int i = 0; i <= 60; i++) {
      setServo(10, 60 + i);
      if (!wav->loop()) wav->stop();
      delay(10);
    }
    for (int i = 0; i <= 60; i++) {
      setServo(10, 120 - i);
      if (!wav->loop()) wav->stop();
      delay(10);
    }
  }
  for (int i = 0; i <= 180; i++) {
    setServo(8, 180 - i);
    if (i <= 90) {
      setServo(9, 90 - i);
    }
    if (i <= 40) {
      setServo(10, 60 - i);
    }
    if (!wav->loop()) wav->stop();
    delay(10);
  }
  delay(3000);
}

/******************** my name is hash ********************/
void my_name_hash() {

  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( mynamehash, sizeof(mynamehash) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  for (int i = 0; i <= 90; i++) {
    setServo(8, 0 + i);
    if (i <= 20) {
      setServo(9, 0 + i);
    }
    delay(10);
  }
  for (int i = 0; i <= 70; i++) {
    setServo(10, 20 + i);
    if (!wav->loop()) wav->stop();
    delay(10);
  }
  for (int i = 0; i <= 70; i++) {
    setServo(10, 90 - i);
    if (!wav->loop()) wav->stop();
    delay(10);
  }
  for (int i = 0; i <= 90; i++) {
    setServo(8, 90 - i);
    if (i <= 20) {
      setServo(9, 20 - i);
    }
    if (!wav->loop()) wav->stop();
    delay(10);
  }
  delay(3000);
}
/******************** nice to meet you too ********************/
void nice_to_meet_you_too() {

  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( nicetomeetyoutoo, sizeof(nicetomeetyoutoo) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  for (int i = 0; i <= 90; i++) {
    setServo(8, 0 + i);
    if (i <= 20) {
      //setServo(9, 0 + i);
      setServo(1, 180 - i);
      setServo(2, 160 - i);
    }
    if (!wav->loop()) wav->stop();
    delay(15);
  }
  for (int i = 0; i <= 90; i++) {
    setServo(8, 90 - i);
    if (i <= 20) {
      //setServo(9, 20 - i);
      setServo(1, 160 + i);
      setServo(2, 140 + i);
    }
    if (!wav->loop()) wav->stop();
    delay(15);
  }
  delay(3000);
}

/******************** i am humanoid robot ********************/
void i_am_humanoid_robot() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( iamhumanoid, sizeof(iamhumanoid) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  for (int i = 0; i <= 90; i++) {
    setServo(8, 0 + i);
    if (i <= 20) {
      setServo(9, 0 + i);
      setServo(1, 180 - i);
      setServo(2, 160 - i * 2);
    }
    if (!wav->loop()) wav->stop();
    delay(15);
  }
  for (int i = 0; i <= 70; i++) {
    setServo(10, 20 + i);
    if (!wav->loop()) wav->stop();
    delay(15);
  }
  for (int i = 0; i <= 70; i++) {
    setServo(10, 90 - i);
    if (!wav->loop()) wav->stop();
    delay(15);
  }
  for (int i = 0; i <= 90; i++) {
    setServo(8, 90 - i);
    if (i <= 20) {
      setServo(9, 20 - i);
      setServo(1, 160 + i);
      setServo(2, 120 + i * 2);
    }
    if (!wav->loop()) wav->stop();
    delay(15);
  }
  delay(3000);
}

/******************** thank you ********************/
void thank_you() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( thankyou, sizeof(thankyou) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  for (int i = 0; i <= 60; i++) {
    setServo(8, 0 + i);
    if (i <= 20) {
      setServo(1, 180 - i);
    }
    if (!wav->loop()) wav->stop();
    delay(15);
  }
  for (int i = 0; i <= 60; i++) {
    setServo(8, 60 - i);
    if (i <= 20) {
      setServo(1, 160 + i);
    }
    if (!wav->loop()) wav->stop();
    delay(15);
  }
  delay(3000);
}

/******************** yes ********************/
void say_yes() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( sayyes, sizeof(sayyes) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  for (int i = 0; i <= 30; i++) {
    setServo(0, 180 - i);
    setServo(1, 180 - i);
    setServo(8, 0 + i);
    setServo(9, 0 + i);
    if (!wav->loop()) wav->stop();
    delay(15);
  }
  for (int i = 0; i <= 30; i++) {
    setServo(0, 150 + i);
    setServo(1, 150 + i);
    setServo(8, 30 - i);
    setServo(9, 30 - i);
    if (!wav->loop()) wav->stop();
    delay(15);
  }
  delay(3000);
}

/******************** no ********************/
void say_no() {

  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( sayno, sizeof(sayno) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  for (int i = 0; i <= 30; i++) {
    headservo.write(90 + i);
    delay(10);
  }
  for (int i = 0; i <= 60; i++) {
    headservo.write(120 - i);
    if (!wav->loop()) wav->stop();
    delay(10);
  }
  for (int i = 0; i <= 30; i++) {
    headservo.write(60 + i);
    if (!wav->loop()) wav->stop();
    delay(10);
  }
  delay(3000);
}

//******************** subscribe ********************//
void say_subscribe() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( subscribe, sizeof(subscribe) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  for (int i = 0; i <= 90; i++) {
    setServo(8, 0 + i);
    setServo(0, 180 - i);
    if (!wav->loop()) wav->stop();
    delay(15);
  }
  for (int i = 0; i <= 60; i++) {
    setServo(0, 90 + i);
    if (!wav->loop()) wav->stop();
    delay(15);
  }
  for (int i = 0; i <= 90; i++) {
    setServo(8, 90 - i);
    if (i <= 30) {
      setServo(0, 150 + i);
    }
    if (!wav->loop()) wav->stop();
    delay(15);
  }
  delay(3000);
}

//******************** bye ********************//
void say_bye() {
  AudioGeneratorWAV *wav;
  AudioFileSourcePROGMEM *file;
  AudioOutputI2SNoDAC *out;

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM( bye, sizeof(bye) );
  out = new AudioOutputI2SNoDAC();
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  for (int i = 0; i <= 180; i++) {
    setServo(8, 0 + i);
    if (i <= 90) {
      setServo(9, 0 + i);
    }
    if (i <= 40) {
      setServo(10, 20 + i);
    }
    delay(10);
  }
  for (int i = 1; i <= 1; i++) {
    for (int i = 0; i <= 60; i++) {
      setServo(10, 60 + i);
      if (!wav->loop()) wav->stop();
      delay(10);
    }
    for (int i = 0; i <= 60; i++) {
      setServo(10, 120 - i);
      if (!wav->loop()) wav->stop();
      delay(10);
    }
  }
  for (int i = 0; i <= 180; i++) {
    setServo(8, 180 - i);
    if (i <= 90) {
      setServo(9, 90 - i);
    }
    if (i <= 40) {
      setServo(10, 60 - i);
    }
    delay(10);
  }
}
// FIM CODE.