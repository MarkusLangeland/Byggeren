#include "pid.h"

const float K_i_value = 1;
const float K_p_value = 0.5;
const float pid_time_step = 500; //change value later 

void pid_init(pid_values *PID){
	PID->K_i = K_i_value; 
	PID->K_p = K_p_value; 
	PID->error = 0; 
	PID->T = pid_time_step; 
}

void pid_controller(pid_values *PID, CAN_MESSAGE *message){
	
	uint8_t yref = (uint8_t)message->data[0];
	uint8_t decoder_value = motor_encoder()/2; 
	
	int sample_time_us = 100; 
	PID->error = yref - decoder_value; 
	
	//printf("%d\n\r", decoder_value);
	//printf("%d\n\r", PID->error); 
	
	
	////calculate gains
	//p_gain = K_p*error;
	//i_gain = K_i*T*error_sum;
	//gain = i_gain + p_gain;
	//
	//error = 0;
	//error_sum =0;
	//return gain;
}
