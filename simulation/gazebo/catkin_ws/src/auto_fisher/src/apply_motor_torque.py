import rospy
from gazebo_msgs.srv import ApplyBodyWrench, ApplyJointEffort
from geometry_msgs.msg import Pose, Quaternion, Point, PoseStamped, PoseWithCovariance, TwistWithCovariance, Twist, Vector3, Wrench
import time

rospy.init_node('apply_effort')
pub_freq = 20
rate = rospy.Rate(pub_freq) # 100 Hz

rospy.wait_for_service("/gazebo/apply_joint_effort")

apply_joint_effort= rospy.ServiceProxy("/gazebo/apply_joint_effort", ApplyJointEffort)


duration = 50 # 100*0.1 = 10 seconds

apply_joint_effort(
                 joint_name = "auto_fisher::joint1",
                 effort = -300,
                 # start_time = rospy.Time(0.1),
                 duration = rospy.Duration(10)
                 )


# for i in range(duration):
#     apply_body_wrench(
#                      body_name = "auto_fisher::shaft_pole",
#                      reference_frame = "auto_fisher::shaft_pole",
#                      reference_point = Point(x=0, y= 3, z=0),
#                      wrench = wrench,
#                      duration = rospy.Duration(0.03)
#                      )
#     rate.sleep()
