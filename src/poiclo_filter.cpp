// C
#include <iostream>
// ROS
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
// PCL
#include <pcl/filters/passthrough.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>


ros::Publisher pub;

void cloud_cb(const pcl::PCLPointCloud2ConstPtr& cloud)
{
    pcl::PCLPointCloud2::Ptr cloud_ptr(new pcl::PCLPointCloud2);


    pcl::PassThrough<pcl::PCLPointCloud2> ptr_filter;

    //pass through filter
    ptr_filter.setInputCloud (cloud);
    ptr_filter.setFilterFieldName("z");
    ptr_filter.setFilterLimits(-0.3,20.0);
    ptr_filter.filter (*cloud_ptr);


    // Publish the data
    pub.publish(*cloud_ptr);
}

int main (int argc, char** argv){
// Initialize ROS
ros::init (argc, argv, "poiclo");
ros::NodeHandle nh;

//subscriber
ros::Subscriber sub = nh.subscribe ("/velodyne_points", 1, cloud_cb);

//publisher 
pub = nh.advertise<sensor_msgs::PointCloud2> ("poiclo_filter/points", 1);

// Spin
ros::spin ();
}
