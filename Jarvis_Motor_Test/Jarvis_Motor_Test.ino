#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define RIGHT_SPEED 10
#define LEFT_SPEED 11

void setup() {

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(RIGHT_SPEED, OUTPUT);
  pinMode(LEFT_SPEED, OUTPUT);
}

void loop() {

  analogWrite(RIGHT_SPEED,0);
  analogWrite(LEFT_SPEED, 0);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
