#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

float joint_pose[12];
int joint_pwm[12];
                         //board pin analog zero  max   min  90   180  0
int servo_config[12][9] = {{0,   0,  A0,    1550, 2550, 550, 323, 512, 134},   //RF_HAA
                           {0,   3,  A1,    1560, 2610, 510, 352, 586, 118},   //RF_HFE
                           {0,   4,  A2,    1580, 2580, 580, 346, 565, 127},   //RF_KFE

                           {0,   7,  A3,    1450, 2500, 400, 317, 514, 120},   //LF_HAA      
                           {1,   0,  A4,    1460, 2460, 460, 313, 534, 92},    //LF_HFE
                           {1,   3,  A5,    1420, 2420, 420, 325, 505, 145},   //LF_KFE

                           {1,   4,  A6,    1420, 2420, 420, 307, 504, 110},   //RH_HAA
                           {1,   7,  A7,    1310, 2370, 250, 318, 507, 129},   //RH_HFE
                           {2,   0,  A8,    1470, 2410, 530, 333, 539, 127},   //RH_KFE

                           {2,   3,  A9,    1540, 2540, 540, 307, 512, 102},   //LH_HAA
                           {2,   4,  A10,   1590, 2630, 550, 326, 477, 175},   //LH_HFE
                           {2,   7,  A11,   1620, 2620, 620, 0,   0,   0}};    //LH_KFE
                           
Adafruit_PWMServoDriver pwm[3] = {Adafruit_PWMServoDriver(0x40), Adafruit_PWMServoDriver(0x41), Adafruit_PWMServoDriver(0x42)};

uint8_t id = 5;
uint8_t board = 1;
uint8_t servonum= 3; 
uint8_t analog_pin = A5;

int pos = 0;

String readString;

void setup() {
  Serial.begin(9600);

  for(int i=0;i<3;i++){
    pwm[i].begin();
    pwm[i].setPWMFreq(50);  
    delay(100);
  }

  for(int i =0; i<12; i++){
    joint_pose[i]= 0.0;
    joint_pwm[i] = radian_to_pwm(joint_pose[i], servo_config[i][4], servo_config[i][5]);
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

  pos = joint_pwm[id];
  
  Serial.println("For example 100+ to 200-");  
  Serial.println();
   
  Serial.println("Centre point:");  
  Serial.println(pos);  
  delay(100);
}

void loop()
{
  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the string readString
    delay(2);  //slow looping to allow buffer to fill with next character
  }
  if (readString.length() >0) {

    if(readString.indexOf('x') >0) {
      pos = readString.toInt();
    }

    if(readString.indexOf('+') >0) {
      pos = pos + readString.toInt();
    }

    if(readString.indexOf('-') >0) {
      pos = pos - readString.toInt();
    }

    pwm[board].writeMicroseconds(servonum, pos);
    Serial.println(pos);
    readString=""; //empty for next input
    
    Serial.println(analogRead(analog_pin));
    Serial.println("");
  }
}


int radian_to_pwm(float radian, int min_pulse, int max_pulse){
   return map(radian, -1.57, 1.57, min_pulse, max_pulse);  
}
