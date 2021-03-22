import rospy
from gazebo_msgs.srv import ApplyBodyWrench
from geometry_msgs.msg import Pose, Quaternion, Point, PoseStamped, PoseWithCovariance, TwistWithCovariance, Twist, Vector3, Wrench
import time
rospy.wait_for_service("/gazebo/apply_body_wrench")

apply_body_wrench= rospy.ServiceProxy("/gazebo/apply_body_wrench", ApplyBodyWrench)

wrench = Wrench()
wrench.force.x = 0
wrench.force.y = 0
wrench.force.z = -300
wrench.torque.x = 6
wrench.torque.y = 0
wrench.torque.z = 0

duration = 100 # 100*0.1 = 10 seconds

for i in range(duration):
    apply_body_wrench(body_name = "auto_fisher::shaft_pole",
                     reference_frame = "auto_fisher::shaft_pole",
                     reference_point = Point(x=0, y= 3, z=0),
                     wrench = wrench,
                     duration = rospy.Duration(0.01))
    time.sleep(0.1)
