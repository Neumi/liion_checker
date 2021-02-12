

int led = 6;
int load_pwm_pin = 5;
int chrge_enable_pin = 4;
int volt_detect_pin = A0;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led, OUTPUT);
  pinMode(chrge_enable_pin, OUTPUT);
  pinMode(load_pwm_pin, OUTPUT);

  digitalWrite(chrge_enable_pin, LOW);
  analogWrite(load_pwm_pin, 0);
}

// the loop function runs over and over again forever
void loop() {
  dischargeOff();

  if(checkVoltage() > 3880) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
  
  chargeOn();
  delay(4000);
  chargeOff();
  delay(4000);
}


void chargeOff() {
  digitalWrite(chrge_enable_pin, LOW);
  delay(50);
}
void chargeOn() {
  digitalWrite(chrge_enable_pin, HIGH);
  delay(50);
}

void dischargeOn() {
  analogWrite(load_pwm_pin, 255);
  delay(50);
}

void dischargeOff() {
  analogWrite(load_pwm_pin, 0);
  delay(50);
}

int checkVoltage() {
  int analog = analogRead(volt_detect_pin);
  int voltage = map(analog, 0,1023, 0, 5000);
  return voltage;
}
