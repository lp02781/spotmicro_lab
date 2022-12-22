#include <ros.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <std_msgs/Float64.h>

float joint_pose[12];
int joint_pwm[12];
                          //board pin analog zero  max   min  90   180  0    Reverse
int servo_config[12][10] = {{0,   0,  A0,    1550, 2550, 550, 323, 512, 134, 1},   //RF_HAA
                            {0,   3,  A1,    1560, 2610, 510, 352, 586, 118, 1},   //RF_HFE
                            {0,   4,  A2,    1580, 2580, 580, 346, 565, 127, 1},   //RF_KFE

                            {0,   7,  A3,    1450, 2500, 400, 317, 514, 120, 0},   //LF_HAA      
                            {1,   0,  A4,    1460, 2460, 460, 313, 534, 92,  0},    //LF_HFE
                            {1,   3,  A5,    1420, 2420, 420, 325, 505, 145, 0},   //LF_KFE

                            {1,   4,  A6,    1420, 2420, 420, 307, 504, 110, 1},   //RH_HAA
                            {1,   7,  A7,    1310, 2370, 250, 318, 507, 129, 1},   //RH_HFE
                            {2,   0,  A8,    1470, 2410, 530, 333, 539, 127, 1},   //RH_KFE

                            {2,   3,  A9,    1540, 2540, 540, 307, 512, 102, 0},   //LH_HAA
                            {2,   4,  A10,   1590, 2630, 550, 326, 477, 175, 0},   //LH_HFE
                            {2,   7,  A11,   1620, 2620, 620, 0,   0,   0,   1}};    //LH_KFE

float servo_standing[12] = {-0.0, 0.81, -1.36,
                            0.0, 0.81, -1.36,
                            0.0, 0.62, -1.36,
                            -0.0, 0.62, -1.36};
                                                        
Adafruit_PWMServoDriver pwm[3] = {Adafruit_PWMServoDriver(0x40), Adafruit_PWMServoDriver(0x41), Adafruit_PWMServoDriver(0x42)};

ros::NodeHandle nh;

std_msgs::Float64 servo_msg;
ros::Publisher pub_servo_output("/servo_output", &servo_msg);

void message_fr_1_cb( const std_msgs::Float64& msg){
  joint_pose[0]=msg.data; 
  servo_msg.data=joint_pose[0];
  pub_servo_output.publish( &servo_msg );
}

void message_fr_2_cb( const std_msgs::Float64& msg){
  joint_pose[1]=msg.data; 
}

void message_fr_3_cb( const std_msgs::Float64& msg){
  joint_pose[2]=msg.data; 
}

void message_fl_1_cb( const std_msgs::Float64& msg){
  joint_pose[3]=msg.data; 
}

void message_fl_2_cb( const std_msgs::Float64& msg){
  joint_pose[4]=msg.data; 
}

void message_fl_3_cb( const std_msgs::Float64& msg){
  joint_pose[5]=msg.data; 
}

void message_rr_1_cb( const std_msgs::Float64& msg){
  joint_pose[6]=msg.data; 
}

void message_rr_2_cb( const std_msgs::Float64& msg){
  joint_pose[7]=msg.data; 
}

void message_rr_3_cb( const std_msgs::Float64& msg){
  joint_pose[8]=msg.data; 
}

void message_rl_1_cb( const std_msgs::Float64& msg){
  joint_pose[9]=msg.data; 
}

void message_rl_2_cb( const std_msgs::Float64& msg){
  joint_pose[10]=msg.data; 
}

void message_rl_3_cb( const std_msgs::Float64& msg){
  joint_pose[11]=msg.data; 
}

ros::Subscriber<std_msgs::Float64> sub_fr_1("/arduino/FR1_joint/command", &message_fr_1_cb );
ros::Subscriber<std_msgs::Float64> sub_fr_2("/arduino/FR2_joint/command", &message_fr_2_cb );
ros::Subscriber<std_msgs::Float64> sub_fr_3("/arduino/FR3_joint/command", &message_fr_3_cb );

ros::Subscriber<std_msgs::Float64> sub_fl_1("/arduino/FL1_joint/command", &message_fl_1_cb );
ros::Subscriber<std_msgs::Float64> sub_fl_2("/arduino/FL2_joint/command", &message_fl_2_cb );
ros::Subscriber<std_msgs::Float64> sub_fl_3("/arduino/FL3_joint/command", &message_fl_3_cb );

ros::Subscriber<std_msgs::Float64> sub_rr_1("/arduino/RR1_joint/command", &message_rr_1_cb );
ros::Subscriber<std_msgs::Float64> sub_rr_2("/arduino/RR2_joint/command", &message_rr_2_cb );
ros::Subscriber<std_msgs::Float64> sub_rr_3("/arduino/RR3_joint/command", &message_rr_3_cb );

ros::Subscriber<std_msgs::Float64> sub_rl_1("/arduino/RL1_joint/command", &message_rl_1_cb );
ros::Subscriber<std_msgs::Float64> sub_rl_2("/arduino/RL2_joint/command", &message_rl_2_cb );
ros::Subscriber<std_msgs::Float64> sub_rl_3("/arduino/RL3_joint/command", &message_rl_3_cb );

void setup() {
  nh.initNode();
  nh.subscribe(sub_fr_1);
  nh.subscribe(sub_fr_2);
  nh.subscribe(sub_fr_3);

  nh.subscribe(sub_fl_1);
  nh.subscribe(sub_fl_2);
  nh.subscribe(sub_fl_3);

  nh.subscribe(sub_rr_1);
  nh.subscribe(sub_rr_2);
  nh.subscribe(sub_rr_3);
  
  nh.subscribe(sub_rl_1);
  nh.subscribe(sub_rl_2);
  nh.subscribe(sub_rl_3);
  
  nh.advertise(pub_servo_output);

  delay(1000);
  for(int i=0;i<3;i++){
    pwm[i].begin();
    pwm[i].setPWMFreq(50);  
    delay(100);
  }

  for(int i =0; i<12; i++){
    joint_pose[i]= servo_standing[i];
    joint_pwm[i] = radian_to_pwm(joint_pose[i], servo_config[i][4], servo_config[i][5], servo_config[i][9]);
  }

  pwm[0].writeMicroseconds(servo_config[0][1], joint_pwm[0]);
  pwm[0].writeMicroseconds(servo_config[1][1], joint_pwm[1]);
  pwm[0].writeMicroseconds(servo_config[2][1], joint_pwm[2]);
  pwm[0].writeMicroseconds(servo_config[3][1], joint_pwm[3]);
  pwm[1].writeMicroseconds(servo_config[4][1], joint_pwm[4]);
  pwm[1].writeMicroseconds(servo_config[5][1], joint_pwm[5]);
  pwm[1].writeMicroseconds(servo_config[6][1], joint_pwm[6]);
  pwm[1].writeMicroseconds(servo_config[7][1], joint_pwm[7]);
  pwm[2].writeMicroseconds(servo_config[8][1], joint_pwm[8]);
  pwm[2].writeMicroseconds(servo_config[9][1], joint_pwm[9]);
  pwm[2].writeMicroseconds(servo_config[10][1], joint_pwm[10]);
  pwm[2].writeMicroseconds(servo_config[11][1], joint_pwm[11]);

  delay(1000);
}

void loop()
{
  nh.spinOnce();
  nh.spinOnce();
  nh.spinOnce(); 

  for(int i =0; i<12; i++){
    joint_pwm[i] = radian_to_pwm(joint_pose[i], servo_config[i][4], servo_config[i][5], servo_config[i][9]);
  }
  pwm[0].writeMicroseconds(servo_config[0][1], joint_pwm[0]);
  pwm[0].writeMicroseconds(servo_config[1][1], joint_pwm[1]);
  pwm[0].writeMicroseconds(servo_config[2][1], joint_pwm[2]);
  pwm[0].writeMicroseconds(servo_config[3][1], joint_pwm[3]);
  pwm[1].writeMicroseconds(servo_config[4][1], joint_pwm[4]);
  pwm[1].writeMicroseconds(servo_config[5][1], joint_pwm[5]);
  pwm[1].writeMicroseconds(servo_config[6][1], joint_pwm[6]);
  pwm[1].writeMicroseconds(servo_config[7][1], joint_pwm[7]);
  pwm[2].writeMicroseconds(servo_config[8][1], joint_pwm[8]);
  pwm[2].writeMicroseconds(servo_config[9][1], joint_pwm[9]);
  pwm[2].writeMicroseconds(servo_config[10][1], joint_pwm[10]);
  pwm[2].writeMicroseconds(servo_config[11][1], joint_pwm[11]);

}

float mapf(float x, float in_min, float in_max, int out_min, int out_max) {
     float result;
     result = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
     return result;
}

int radian_to_pwm(float radian, int min_pulse, int max_pulse, int inverse_status){
   float haha = 0.0;
   if(inverse_status){
        radian = -1*radian;
   }
   haha = mapf(radian, -1.57, 1.57, min_pulse, max_pulse);  
   return haha;
}
