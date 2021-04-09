import rospy
from gazebo_msgs.srv import ApplyBodyWrench
from geometry_msgs.msg import Pose, Quaternion, Point, PoseStamped, PoseWithCovariance, TwistWithCovariance, Twist, Vector3, Wrench, WrenchStamped
import time
import std_msgs.msg
import numpy as np
from control_msgs.msg import JointControllerState
import matplotlib.pyplot as plt

class DataLogger():
    def __init__(self):
        self.time_list = []
        self.actual_position_list = []
        self.set_point_list = []
        self.torque_list =[]
        self.time = 0
        self.pub_freq = 10
        self.pub_period = 1/self.pub_freq
        rospy.on_shutdown(self.plot_data)
        self.force_list = []
        self.force_time_list = []

    def callback(self, msg):
        self.actual_position_list.append(msg.process_value)
        self.set_point_list.append(msg.set_point)
        self.time_list.append(self.time*0.01)
        self.torque_list.append(msg.command)
        self.time +=1

    def ft_callback(self, data):
        self.force_list.append(data.wrench.force.z)
        self.force_time_list.append(self.time*0.01)
        self.time +=1

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

        rospy.spin()

    def plot_data(self):
        fig, axs= plt.subplots(3,1, sharex = True)

        axs[0].plot(self.time_list, self.actual_position_list, label = "position")
        axs[0].plot(self.time_list, self.set_point_list, label = "setpoint")
        axs[0].set_ylim(-3, 1)
        # plt.xlim(0,15)
        axs[0].set_xlabel("Time (s)")
        axs[0].set_ylabel("Position (rad)")
        axs[0].legend()

        axs[1].plot(self.force_time_list, self.force_list, label = "force", color = 'green')
        axs[1].set_ylim(-400,600)
        axs[1].set_xlabel("Time (s)")
        axs[1].set_ylabel("Force (N)")

        axs[2].plot(self.time_list, self.torque_list, label = "torque", color = 'red')
        axs[2].set_ylim(-600,600)
        axs[2].set_xlabel("Time (s)")
        axs[2].set_ylabel("Motor Torque (Nm)")

        fig.tight_layout()
        plt.show()

if __name__ == "__main__":
    rospy.init_node('trajectory_plotter')
    data_logger = DataLogger()
    data_logger.listener()
