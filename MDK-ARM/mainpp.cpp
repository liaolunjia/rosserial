#include <mainpp.h>
#include <ros.h>
#include <std_msgs/String.h>

void command_callback( const std_msgs::String& rxbuff);

ros::NodeHandle nh;

std_msgs::String stm32_to_pc_word;

ros::Subscriber<std_msgs::String> cmd_sub("pc_to_stm32", command_callback);
ros::Publisher stm32_to_pc("stm32_to_pc", &stm32_to_pc_word);

void command_callback( const std_msgs::String& rxbuff)
{
    stm32_to_pc_word = rxbuff;
		stm32_to_pc.publish(&stm32_to_pc_word);
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->reset_rbuf();
}

void setup(void)
{
  nh.initNode();
	nh.advertise(stm32_to_pc);
	nh.subscribe(cmd_sub);
}

void loop(void)
{  
	HAL_Delay(500);
	nh.spinOnce();
}

