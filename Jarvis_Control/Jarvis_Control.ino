#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Vector3Stamped.h>

#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define RIGHT_SPEED 10
#define LEFT_SPEED 11
#define LOOPTIME 100

int spd = 0;
float x;
float z;

ros::NodeHandle nh;

void velCallback (const geometry_msgs::Twist& vel) {
  float X = vel.linear.x;
  float Z = vel.angular.z;
  x = X * 100;
  z = Z * 100;
  if (z > 0) {
    z = map(z, 0, 284, 0, 22);
  }
  else {
    z = map(z, 0, -284, 0, -22);
  }
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", velCallback);
geometry_msgs::Vector3Stamped speed_msg;
ros::Publisher speed_pub("speed", &speed_msg);
void setup() {

  //  Serial.begin(57600);
  nh.initNode();
  nh.getHardware() -> setBaud(57600);
  nh.subscribe(sub);
  nh.advertise(speed_pub);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(RIGHT_SPEED, OUTPUT);
  pinMode(LEFT_SPEED, OUTPUT);
}

void loop() {

  if (z > 0 && x == 0) {

    int spd = map(z, 1, 22, 50, 255);
    analogWrite(RIGHT_SPEED, spd);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

  else if (z < 0 && x == 0) {

    int spd = map(z, -1, -22, 50, 255);
    analogWrite(LEFT_SPEED, spd);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }

  else if (x > 0) {

    int spd = map(x, 1, 22, 50, 255);
    if (z == 0) {
      analogWrite(RIGHT_SPEED, spd);
      analogWrite(LEFT_SPEED, spd);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
    else if (z > 0) {
      int choice = (x < z ? 1 : 2);
      switch (choice) {
        case 1: {            // x < z
            int right_spd = map(z, 1, 22, 50, 255);
            analogWrite(RIGHT_SPEED, right_spd);
            analogWrite(LEFT_SPEED, spd);
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
            break;
          }
        case 2: {           // x == z or x > z
            analogWrite(RIGHT_SPEED, spd);
            analogWrite(LEFT_SPEED, spd);
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
            break;
          }
      }
    }
    else if (z < 0) {
      int temp_z = z * -1;
      int choice = x < temp_z ? 1 : 2;
      switch (choice) {
        case 1: {
            int left_spd = map(z, -1, -22, 50, 255);
            analogWrite(RIGHT_SPEED, spd);
            analogWrite(LEFT_SPEED, left_spd);
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
            break;
          }
        case 2: {
            analogWrite(RIGHT_SPEED, spd);
            analogWrite(LEFT_SPEED, spd);
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
            break;
          }
      }
    }
  }

  else if (x < 0) {
    int spd = map(x, -1, -22, 50, 255);
    analogWrite(RIGHT_SPEED, spd);
    analogWrite(LEFT_SPEED, spd);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }

  else {

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  publishSpeed(LOOPTIME);
}

void publishSpeed(double time) {

  //  char *log_msg;
  speed_msg.header.stamp = nh.now();
  speed_msg.vector.x = x;
  speed_msg.vector.y = z;
  speed_msg.vector.z = time / 1000;
  speed_pub.publish(&speed_msg);
  nh.spinOnce();
  //  sprintf(log_msg, "%f\t%f", x, z);
  //  nh.loginfo(log_msg);
}
