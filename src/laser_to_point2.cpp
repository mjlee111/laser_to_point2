#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>

ros::Publisher pub;

void laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
  for (int i = 0; i < scan->ranges.size(); i++) {
    float angle = scan->angle_min + i * scan->angle_increment;
    pcl::PointXYZ point;
    point.x = scan->ranges[i] * cos(angle);
    point.y = scan->ranges[i] * sin(angle);
    point.z = 0;
    cloud->push_back(point);
  }

  sensor_msgs::PointCloud2 output;
  pcl::toROSMsg(*cloud, output);
  output.header.frame_id = scan->header.frame_id;
  output.header.stamp = scan->header.stamp;
  pub.publish(output);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "laser_to_pointcloud");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe<sensor_msgs::LaserScan>("scan", 1, laserScanCallback);
  pub = nh.advertise<sensor_msgs::PointCloud2>("pointcloud", 1);
  ros::spin();
  return 0;
}

