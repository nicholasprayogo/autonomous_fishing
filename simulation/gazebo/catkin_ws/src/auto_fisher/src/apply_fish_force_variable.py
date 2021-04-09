import rospy
from gazebo_msgs.srv import ApplyBodyWrench
from geometry_msgs.msg import Pose, Quaternion, Point, PoseStamped, PoseWithCovariance, TwistWithCovariance, Twist, Vector3, Wrench
import time
import numpy as np

rospy.init_node('apply_force')
pub_freq = 20
rate = rospy.Rate(pub_freq) # 100 Hz

rospy.wait_for_service("/gazebo/apply_body_wrench")

apply_body_wrench= rospy.ServiceProxy("/gazebo/apply_body_wrench", ApplyBodyWrench)

wrench = Wrench()
wrench.force.x = 0
wrench.force.y = 0
wrench.force.z = -150
wrench.torque.x = 0
wrench.torque.y = 0
wrench.torque.z = 0

duration = 30 # 100*0.1 = 10 seconds

# apply_body_wrench(
#                  body_name = "auto_fisher::shaft_pole",
#                  reference_frame = "auto_fisher::shaft_pole",
#                  reference_point = Point(x=0, y= 3, z=0),
#                  wrench = wrench,
#                  duration = rospy.Duration(3)
#                  )
#
# time.sleep(5)

# wrench_list = np.linspace(-1200, -300, duration)

# possible_forces = [-200, -300, -100]
# wrench_list = list(np.random.choice(possible_forces, duration))
# wrench_list.insert(0, -150)

wrench_list = [-150] * duration
# wrench_list = [-500, -1000, -800, -400, -300, -200,
#                 -150, -300, -200, -100, -300, -100, -300, -150, -100]
# wrench_list =  np.flip(wrench_list)

for index, i in enumerate(range(duration)):
    wrench = Wrench()
    wrench.force.x = 0
    wrench.force.y = 0
    wrench.force.z = wrench_list[index]
    wrench.torque.x = 0
    wrench.torque.y = 0
    wrench.torque.z = 0
    if index == 0:
        wrench_duration = 0.05
    else:
        wrench_duration = 0.05

    apply_body_wrench(
                     body_name = "auto_fisher::shaft_pole",
                     reference_frame = "auto_fisher::shaft_pole",
                     reference_point = Point(x=0, y= 3, z=0),
                     wrench = wrench,
                     duration = rospy.Duration(wrench_duration)
                     )
    rate.sleep()
