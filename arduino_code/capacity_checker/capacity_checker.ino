#include <SoftwareSerial.h>

SoftwareSerial mySerial(A4, A5);


int led = 6;
int load_pwm_pin = 5;
int chrge_enable_pin = 4;
int volt_detect_pin = A0;

void setup() {
  mySerial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(chrge_enable_pin, OUTPUT);
  pinMode(load_pwm_pin, OUTPUT);

  digitalWrite(chrge_enable_pin, LOW);
  analogWrite(load_pwm_pin, 0);
}

void loop() {
  delay(1000);
  dischargeUntilEmpty();
}

void dischargeUntilEmpty() {
  int voltage = checkVoltage();
  mySerial.println(voltage);
  if (voltage > 3200) {
    dischargeOn();
  } else {
    dischargeOff();
  }
}


void dischargeOn() {
  // mySerial.println("discharging ON");
  /* 10 = 222
     15 = 320
     20 = 426
     22 = 474
     23 = 495
     24 = 516
     25 = 530ma
     40 = 830ma
  */
  analogWrite(load_pwm_pin, 23);
  digitalWrite(led, HIGH);
  delay(10);
}

void dischargeOff() {
  // mySerial.println("discharging OFF");
  analogWrite(load_pwm_pin, 0);
  digitalWrite(led, LOW);
  delay(10);
}

int checkVoltage() {
  int analog = analogRead(volt_detect_pin);
  int voltage = map(analog, 0, 1023, 0, 5000);
  return voltage;
}
