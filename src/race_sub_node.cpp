#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

int adjust = 0;
void laserCallback(sensor_msgs::LaserScan scan){
	ROS_INFO("INFO: [%f]", scan.ranges[90]);
//	ROS_INFO("INFO: [%f]", scan.ranges.size());
//	ROS_INFO("angle min: [%f]", scan.angle_min);
//	ROS_INFO("angle max: [%f]", scan.angle_max);

	if(scan.ranges[65] < 3.5 && scan.ranges[90] < 5){adjust = 5;}
	if(scan.ranges[125] < 3.5&& scan.ranges[90] < 5){adjust = -5;}
}
int main(int argc, char **argv){
  ros::init(argc, argv, "race_solver");
  ros::NodeHandle n;
  ros::Subscriber lasersub = n.subscribe("/robot/base_scan",1000,laserCallback);
  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/robot/cmd_vel",1000);

  ros::Rate loop_rate(10);
  while(ros::ok()){
  geometry_msgs::Twist msg;
  msg.linear.x = 2.4;
  msg.angular.z = adjust;
  adjust = 0;
  pub.publish(msg);

  ros::spinOnce();
  loop_rate.sleep();}
  return 0;

}
