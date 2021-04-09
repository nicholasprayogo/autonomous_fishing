import rospy
from gazebo_msgs.srv import ApplyBodyWrench
from geometry_msgs.msg import Pose, Quaternion, Point, PoseStamped, PoseWithCovariance, TwistWithCovariance, Twist, Vector3, Wrench, WrenchStamped
from control_msgs.msg import JointControllerState
import time
import std_msgs.msg
import numpy as np

# check if exerted torque exceeds 'fisher_robot/joint1_position_controller/state/command
import signal

import time   # For the demo only

def signal_handler(signal, frame):
    global interrupted
    interrupted = True

signal.signal(signal.SIGINT, signal_handler)

class FishPull():
    def __init__(self):
        self.rate = rospy.Rate(pub_freq) # 100 Hz
        self.pub = rospy.Publisher('fisher_robot/joint1_position_controller/command', std_msgs.msg.Float64, queue_size=10)
        self.executing_pull = False
        self.angle_threshold = 0.5
        self.current_position = None
        self.force_z = 0
        self.force_threshold = 100

    def callback(self, data):
        self.current_position = data.process_value


    def ft_callback(self, data):
        self.force_z = data.wrench.force.z


    def listener(self):
        rospy.Subscriber("/fisher_robot/joint1_position_controller/state/",
            JointControllerState,
            self.callback,
            queue_size = 1,
            tcp_nodelay=True)

        rospy.Subscriber("/ft_sensor_topic",
            WrenchStamped,
            self.ft_callback,
            queue_size = 1,
            tcp_nodelay=True)

        # rospy.spin()
        while True:
            print("Position: {}, Force: {}".format(self.current_position, self.force_z))
            if (self.force_z > self.force_threshold) and (self.executing_pull==False):
                print("Pulling fish..")
                self.executing_pull = True
                self.pull_fish()
            elif (self.executing_pull and self.current_position > -2.4):
                self.pull_fish()
            elif (self.executing_pull and self.current_position < -2.4):
                self.return_back()
                time.sleep(5)
                self.executing_pull = False
            else:
                self.pub.publish(std_msgs.msg.Float64(0.2))
            self.rate.sleep()

    def pull_fish(self):
        self.pub.publish(std_msgs.msg.Float64(-2.6))
        # time.sleep(2)

    def return_back(self):
        self.pub.publish(std_msgs.msg.Float64(0.2))

if __name__ =="__main__":
    pub_freq = 20
    force_threshold = 100 # N
    rospy.init_node('pole_trajectory_controller')
    fish_puller = FishPull()
    fish_puller.listener()
