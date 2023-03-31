cmake_minimum_required(VERSION 3.0.2)
project(laser_to_point2)

find_package(catkin REQUIRED COMPONENTS
  pcl_ros
  pcl_conversions
  roscpp
  sensor_msgs
)

catkin_package(
  CATKIN_DEPENDS pcl_ros pcl_conversions roscpp sensor_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(laser_to_pointcloud src/laser_to_point2.cpp)
target_link_libraries(laser_to_pointcloud ${catkin_LIBRARIES})

