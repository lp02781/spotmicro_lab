#!/usr/bin/env python3
#Author: lnotspotl

import rospy
import numpy as np

class StandController(object):
    def __init__(self, default_stance):
        self.def_stance = default_stance
        self.max_reach = 0.065

        self.FR_X = 0.
        self.FR_Y = 0.
        self.FL_X = 0.
        self.FL_Y = 0.

    def updateStateCommand(self,msg,state,command):
        state.body_local_position[0] = msg.axes[5] * 0.14;
        '''
		joystick setting
		0 : left left < 0 left right
		1 : left up < 0 < left down
		2 : right left < 0 <right right
		3 : right up < 0 < right down
		4 : left < 0 < right
		5 : up < 0 < down
		0 : Triangle
		1 : Circle
		2 : X
		3 : Rectangle
		4 : L1
		5 : R1
		6 : L2
		7 : R2 
        '''
        self.FR_X = msg.axes[3]
        self.FR_Y = msg.axes[2]

        self.FL_X = msg.axes[1]
        self.FL_Y = msg.axes[0]

    @property
    def default_stance(self):
        a = np.copy(self.def_stance)
        return a

    def run(self,state,command):
        temp = self.default_stance
        temp[2] = [command.robot_height] * 4
        
        temp[1][0] += self.FR_Y * self.max_reach
        temp[0][0] += self.FR_X * self.max_reach

        temp[1][1] += self.FL_Y * self.max_reach
        temp[0][1] += self.FL_X * self.max_reach
            
        state.foot_locations = temp
        return state.foot_locations
