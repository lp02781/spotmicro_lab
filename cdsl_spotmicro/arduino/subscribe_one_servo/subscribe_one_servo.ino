#include <ros.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Joy.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

ros::NodeHandle  nh;

std_msgs::Float64 servo_msg;
ros::Publisher pub_servo_output("/servo_output", &servo_msg);

float joint_pose=0;
int joint_pwm = 0;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void messageCb( const sensor_msgs::Joy& msg){
  joint_pose=msg.axes[0]; 
  servo_msg.data=joint_pose;
  pub_servo_output.publish( &servo_msg );
}

ros::Subscriber<sensor_msgs::Joy> sub("/servo_input", &messageCb );

void setup()
{ 
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub_servo_output);

  pwm.begin();
  pwm.setPWMFreq(50);
}

void loop()
{  
  nh.spinOnce();
  joint_pwm = radian_to_pwm(joint_pose, 580, 2580);
  
  pwm.writeMicroseconds(4, joint_pwm);
  delay(1);
}

float mapf(float x, float in_min, float in_max, int out_min, int out_max) {
   float result;
   result = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
   return result;
}

int radian_to_pwm(float radian, int min_pulse, int max_pulse){
   float haha = 0.0;
   haha = mapf(radian, -1.57, 1.57, min_pulse, max_pulse);  
   return haha;
}
