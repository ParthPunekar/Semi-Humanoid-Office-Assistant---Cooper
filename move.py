#!/usr/bin/env python

import threading
from threading import *
from time import *

import rospy
from geometry_msgs.msg import Twist

def timer():
	global counter
	counter += 1
	if recall:
		threading.Timer(1.0, timer).start()

def move_cooper():
	
	rospy.init_node('move_cooper', anonymous=True)
	pub = rospy.Publisher('cmd_vel', Twist, queue_size=10)
	rate = rospy.Rate(10)

	vel = Twist()

	while not rospy.is_shutdown():

		if counter > 0 and counter <= 2:
			# Turn Left for 2s
			vel.linear.x = 0
			vel.linear.y = -1
			vel.linear.z = 0

			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = 0

		elif counter > 3 and counter <= 11:
			# Move striaght for 8s
			vel.linear.x = 1
			vel.linear.y = 0
			vel.linear.z = 0

			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = 0

		elif counter > 12 and counter <= 14:
			# Turn Right for 2s
			vel.linear.x = 0
			vel.linear.y = 1
			vel.linear.z = 0

			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = 0

		elif counter > 15 and counter <= 27:
			# Move Striaght for 12s
			vel.linear.x = 1
			vel.linear.y = 0
			vel.linear.z = 0

			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = 0

		elif counter > 28 and counter <= 30:
			# Turn Right for 2s
			vel.linear.x = 0
			vel.linear.y = 1
			vel.linear.z = 0

			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = 0

		elif counter > 31 and counter <= 43:
			# Move Straight for 12s 
			vel.linear.x = 1
			vel.linear.y = 0
			vel.linear.z = 0

			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = 0

		elif counter > 44 and counter <= 46:
			# Turn Right for 2s
			vel.linear.x = 0
			vel.linear.y = 1
			vel.linear.z = 0

			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = 0

		elif counter > 47 and counter <= 59:
			# Move straight for 12s
			vel.linear.x = 1
			vel.linear.y = 0
			vel.linear.z = 0

			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = 0

		elif counter > 60 and counter <= 62:
			# Turn Right for 2s
			vel.linear.x = 0
			vel.linear.y = 1
			vel.linear.z = 0

			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = 0

		elif counter > 62 and counter <= 66:
			# Move straight for 4s
			vel.linear.x = 1
			vel.linear.y = 0
			vel.linear.z = 0

			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = 0

		elif counter > 67 and counter <= 69:
			# Turn Right for 2s
			vel.linear.x = 0
			vel.linear.y = 1
			vel.linear.z = 0

			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = 0

		elif counter > 70 and counter <= 78:
			# Move striaght for 8s
			vel.linear.x = 1
			vel.linear.y = 0
			vel.linear.z = 0

			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = 0

		elif counter > 79 and counter <= 87:
			# Move left for 8s
			vel.linear.x = 0
			vel.linear.y = 0
			vel.linear.z = 0

			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = -1

		elif counter > 88 and counter <= 96:
			# Move Right for 8s
			vel.linear.x = 0
			vel.linear.y = 0
			vel.linear.z = 0

			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = 1

		elif counter > 97 and counter <= 105:
			# Move back for 8s
			vel.linear.x = -1
			vel.linear.y = 0
			vel.linear.z = 0

			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = 0

		else:
			# Stop
			vel.linear.x = 0
			vel.linear.y = 0
			vel.linear.z = 0

			vel.angular.x = 0
			vel.angular.y = 0
			vel.angular.z = 0

		pub.publish(vel)
		rate.sleep()
	recall = False


if __name__ == '__main__':

	recall = True
	counter = 0

	timer()
	try:
		move_cooper()
	except rospy.ROSInterruptException:
		pass