#pragma once
#include "sam.h"
#include <stdint.h>
#include "motor.h"
#include "can_controller.h"

typedef struct {
	float K_p;
	float K_i;
	float error;
	float T;
} pid_values;

void pid_init(pid_values *PID);
void pid_controller(pid_values *PID, CAN_MESSAGE *message);

