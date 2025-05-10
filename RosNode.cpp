#include <gtk/gtk.h>
#include <locale.h>
#include <thread>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#include "ros_node.hpp"


#ifndef RCLCPP_INFO
#define RCLCPP_INFO(this_node, ...) \
  printf(__VA_ARGS__); \
  printf("\n");
#endif

#ifndef RCLCPP_ERROR
#define RCLCPP_ERROR(this_node, ...) \
  printf(__VA_ARGS__); \
  printf("\n");
#endif

#ifndef RCLCPP_WARN

#define RCLCPP_WARN(this_node, ...) \
  printf(__VA_ARGS__); \
  printf("\n");
#endif

#ifndef RCLCPP_DEBUG

#define RCLCPP_DEBUG(this_node, ...) \
  printf(__VA_ARGS__); \
  printf("\n");
#endif

using std::placeholders::_1;

class MyRosNode : public rclcpp::Node {
public:
	MyRosNode ( ) : Node ( "car_ros_node" ) {
		sub_ = this->create_subscription<std_msgs::msg::String> (
		  "/devices/information" , 10 , std::bind ( &MyRosNode::topic_callback , this , _1 ) );
	}

	void ros2_thread_func ( );

private:
	void topic_callback ( const std_msgs::msg::String::SharedPtr msg ) {
		RCLCPP_INFO ( this->get_logger ( ) , "Received: '%s'" , msg->data.c_str ( ) );

		//Read the topics from ros node
	}

	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

void ros2_thread_func ( ) {
	rclcpp::init ( 0 , nullptr );
	rclcpp::spin ( std::make_shared<MyRosNode> ( ) );
	rclcpp::shutdown ( );
}
