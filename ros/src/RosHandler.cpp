#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


class RosNode : public rclcpp::Node

{
	public:
		RosNode()
			: Node("ros_main_node") {


				publisher_ = this->create_publisher<std_msgs::msg::String>("ros_output", 10);

				subscriber_ = this->create_subscription<std_msgs::msg::String>("ros_input", 10)
					


			}
