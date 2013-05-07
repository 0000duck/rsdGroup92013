#!/usr/bin/env python
import roslib; roslib.load_manifest('PLC_INTERFACE')
import rospy
from std_msgs.msg import String
import time
import serial


robTemp = "0"
visTemp = "0"

def write():
	if((robTemp=="1") and (visTemp=="1")):
		ser.write("sta")
		time.sleep(1.75)
		ser.write("sto")
	if((robTemp=="0") and (visTemp=="0")):
		ser.write("sto")

def robCallback(data):
	signal = data.data
	global robTemp
	if(signal!=robTemp):
		robTemp=signal
		write()
		
def visCallback(data):
	signal = data.data
	global visTemp
	if(signal!=visTemp):
		visTemp=signal
		write()
		

def main():
	rospy.init_node('plcControl', anonymous=True)
	rospy.Subscriber("robotReady", String, robCallback)
	rospy.Subscriber("visReady", String, visCallback)
	global ser
	ser = serial.Serial('/dev/ttyUSB0', 19200, timeout=1)
	

		


	ser.open()
	ser.isOpen()
# 	run = 1
#  	while run:
# 		output = raw_input(">> ")
# 		if output == "q":
# 			print "Closing connection!"
# 			exit()
# 		else:
# 			print "Sending data : " + output
# 			ser.write(output)
# 		    
# 	
# 		time.sleep(1)
# 		while ser.inWaiting() > 0:
# 			bits = ser.read(ser.inWaiting())
# 			print "Received data: " + bits
	
	rospy.spin()
	
	


if __name__ == '__main__':
    main()
