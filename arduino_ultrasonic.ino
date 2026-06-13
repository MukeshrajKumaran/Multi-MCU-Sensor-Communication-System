#include <Wire.h>

#define TRIG 9
#define ECHO 10
#define SLAVE_ADDR 8

char data[12];  // fixed 12 bytes

long readDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  if (duration == 0) return -1;

  return duration * 0.034 / 2;
}

long getFilteredDistance() {
  long sum = 0;
  int valid = 0;

  for (int i = 0; i < 5; i++) {
    long d = readDistance();
    if (d > 0 && d < 400) {
      sum += d;
      valid++;
    }
    delay(10);
  }

  if (valid == 0) return -1;
  return sum / valid;
}

void sendData() {
  Wire.write((uint8_t*)data, 12);  
}

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  Wire.begin(SLAVE_ADDR);
  Wire.onRequest(sendData);

  Serial.begin(9600);
}

void loop() {
  long dist = getFilteredDistance();

  if (dist == -1) {
    snprintf(data, sizeof(data), "DIST:ERR ");
  } else {
    snprintf(data, sizeof(data), "DIST:%03ld", dist);
  }

  Serial.println(data);
  delay(2000);
}