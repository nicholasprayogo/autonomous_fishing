import rospy
from gazebo_msgs.srv import ApplyBodyWrench
from geometry_msgs.msg import Pose, Quaternion, Point, PoseStamped, PoseWithCovariance, TwistWithCovariance, Twist, Vector3, Wrench, WrenchStamped
import time
import std_msgs.msg
import numpy as np

# check if exerted torque exceeds 'fisher_robot/joint1_position_controller/state/command

class FishPull():
    def __init__(self):
        self.rate = rospy.Rate(pub_freq) # 100 Hz
        self.pub = rospy.Publisher('fisher_robot/joint1_position_controller/command', std_msgs.msg.Float64, queue_size=10)
        self.executing_pull = False

    def callback(self, data):
        force_exerted_z = data.wrench.force.z
        print(force_exerted_z)
        if (force_exerted_z > force_threshold) and (self.executing_pull==False):
            print("Pulling fish..")
            self.executing_pull = True
            self.pull_fish()

    def listener(self):
        # set queue_size to 1 so force_exerted don't fill up the queue during fish pull
        rospy.Subscriber("/ft_sensor_topic", WrenchStamped, self.callback, queue_size = 1,tcp_nodelay=True)
        # rospy.spin()
        while True:
            if self.executing_pull==False:
                self.pub.publish(std_msgs.msg.Float64(0.2))
            self.rate.sleep()

    def pull_fish(self):
        trajectory = np.linspace(-2.6, 0.2, num = 100)
        trajectory = np.flip(trajectory,0) # in the simulation it goes from positive to negative
        for point in trajectory:
            self.pub.publish(std_msgs.msg.Float64(point))
            self.rate.sleep()

        trajectory_back = np.flip(trajectory, 0)
        for point in trajectory_back:
            self.pub.publish(std_msgs.msg.Float64(point))
            self.rate.sleep()
        self.executing_pull = False
        time.sleep(2)

if __name__ =="__main__":
    pub_freq = 20
    force_threshold = 100 # N
    wrench_data = WrenchStamped()
    rospy.init_node('fish_puller')
    fish_puller = FishPull()
    fish_puller.listener()
