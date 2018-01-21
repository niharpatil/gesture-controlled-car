
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

int left_motor = 6;
int right_motor = 5;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pinMode(left_motor,OUTPUT);
  pinMode(right_motor, OUTPUT);
}

bool moving = false;
bool turning = false;
void loop() {
  if (radio.available()) {
    double txt[32] = {};
    radio.read(&txt, sizeof(txt));
    double value = txt[0];
    Serial.println(value);

    if (value > 300) {
      if (value >= 580 && moving) {
        turnLeft();
        turning = true;
      } else if (value <= 450 && moving){
        turnRight();
        turning = true;
      } else {
        turning = false;
      }
    } else {
      if (value >= 25 && !turning){
        forward();
        moving = true;
      } else if (value < 25) {
        stopWheels();
        moving = false;
      }
    }
  }
}

void turnLeft() {
  digitalWrite(right_motor, LOW);
  digitalWrite(left_motor, HIGH);
}

void turnRight(){
  digitalWrite(left_motor, LOW);
  digitalWrite(right_motor, HIGH);
}

void forward(){
  digitalWrite(left_motor, HIGH);
  digitalWrite(right_motor, HIGH);
}

void stopWheels() {
  digitalWrite(left_motor, LOW);
  digitalWrite(right_motor, LOW);
}


