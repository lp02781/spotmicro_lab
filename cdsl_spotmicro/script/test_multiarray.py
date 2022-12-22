import rospy
from std_msgs.msg import Float64MultiArray
 
def callback(data):
	print(data.data)
        
def listener():
	rospy.init_node('listener', anonymous=True) 
	rospy.Subscriber("/servo_input",Float64MultiArray,callback)
	rospy.spin()
 
if __name__ == '__main__':
	listener()
