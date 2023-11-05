//#include "pwm.h"
//
//#define PERIOD 0.02 //20 ms
//#define PRESCALAR 1024
//#define MCK 84000000
//
//
//#define TRESHOLD_HORISONTAL 60
//#define TRESHOLD_VERTICAL 50
//
//#define DUTY_CYCLE_MIN 0.045 //min is 0.9
//#define DUTY_CYCLE_MAX 0.105 //max is set to 2.1
//static const uint32_t CPRD = PERIOD * MCK / PRESCALAR;
//static const uint32_t F_CHAN_CLOCK = MCK/PRESCALAR;
//
//
//
//void pwm_init() {
	//
	////set the PWM clock
	//PMC->PMC_PCER1 |=PMC_PCER1_PID36;
	 //while ((PMC->PMC_PCSR1 & PMC_PCSR1_PID36) == 0)
	 //{
	 //};
//
	////Peripherals<3
	////disable PIO
	//PIOC->PIO_PDR|= PIO_PDR_P19;
	////Add peripheral B
	//PIOC->PIO_ABSR |= PIO_ABSR_P19;
	////set the modes and values for the PWM
	////Set the prescalar 256
	//PWM->PWM_CLK = PWM_CLK_DIVA(1) | PWM_CLK_PREA(0b1010);
	////Set prescaler 
	////REG_PWM_CMR5 |= 0b0111;
	//PWM->PWM_CH_NUM[5].PWM_CMR = PWM_CMR_CPRE_CLKA | PWM_CMR_CPOL;
//
	////...
	////REG_PWM_CPRD5 |= 0b0011001101000101;
	//PWM->PWM_CH_NUM[5].PWM_CPRD = PWM_CPRD_CPRD(CPRD);
	////REG_PWM_CDTY0 |= 
	//PWM->PWM_ENA |= PWM_ENA_CHID5;
	//
//}
//
//
//servo_directions calculate_direction_servo(CAN_MESSAGE* can_msg) {
	////for (int i = 0; i < can_msg->data_length; i++)
	////{
		////printf("%d ", can_msg->data[i]);
	////}
	////printf("\n\r");
	//int horisontal = can_msg->data[0];
	//int vertical = can_msg->data[4];
	//if (horisontal < -TRESHOLD_HORISONTAL) {
			//return LEFT;
		//} else if(horisontal > TRESHOLD_HORISONTAL) {
			//return RIGHT;
		//} else if(vertical > TRESHOLD_VERTICAL) {
			//return UP;
		//} else {
			//return NEUTRAL;
		//}
	//
//}
//
//
////void pwm_set_servo_position(servo_directions direction) {
	////if (direction == LEFT) {
		////printf(" LEFT ");
		////printf("\n\r");
	////} else if(direction == UP) {
		////printf(" UP ");
		////printf("\n\r");
	////} else if(direction == RIGHT) {
		////printf(" RIGHT ");
		////printf("\n\r");
	////}
	////
////}
//
//void pwm_set_servo(double duty_cycle) {
	////duty_cycle = duty_cycle < DUTY_CYCLE_MIN ? DUTY_CYCLE_MIN : duty_cycle;
	////duty_cycle = duty_cycle > DUTY_CYCLE_MAX ? DUTY_CYCLE_MAX : duty_cycle;
	//
	    //if (duty_cycle < DUTY_CYCLE_MIN)
	    //{
		    //duty_cycle = DUTY_CYCLE_MIN;
	    //}
	    //if (duty_cycle > DUTY_CYCLE_MAX)
	    //{
		    //duty_cycle = DUTY_CYCLE_MAX;
	    //}
		//
	//PWM->PWM_CH_NUM[5].PWM_CMR |= PWM_CMR_CPOL;	
	//PWM->PWM_CH_NUM[5].PWM_CDTY |= (uint32_t)(-1/F_CHAN_CLOCK*(PERIOD*duty_cycle - PERIOD));
//
	////PWM->PWM_CH_NUM[5]
	////PWM->PWM_CH_NUM[5]
//}

#include "pwm.h"
#include "sam.h"


#define MCK         84E6
#define PERIOD		20E-3
#define CPRDA       (int) (PERIOD * MCK / DIVA)

#define DIVA        84
#define DIVB        84
#define CLK_A       1E6
#define CLK_B       1E6

#define DUTY_CYCLE_MIN 0.045 //min is 0.9
#define DUTY_CYCLE_MAX 0.105 //max is set to 2.1

static const uint32_t CLK_PRESCALAR = 1024;
static const double F_CHANNEL_5_CLOCK = MCK / DIVA;
static const uint32_t CPRD = PERIOD * MCK / DIVA;
static const double MIN_DUTY_CYCLE = 0.9 / 20;
static const double MAX_DUTY_CYCLE = 2.1 / 20;
#define WMH6 6
#define WMH5 5

#include "pwm.h"
#include "sam.h"

//void pwm_init() {
	//// enable peripheral function B for PIN45 and PIN44
	//PIOC->PIO_ABSR |= PIO_PC19B_PWMH5 | PIO_PC18B_PWMH6;
//
	//// disable PIO from controlling PIN44 and PIN45
	//PIOC->PIO_PDR |= PIO_PC19B_PWMH5 | PIO_PC18B_PWMH6;
//
	//// enable clock for PWM:    DIV = 0 (clk = MCK), CMD = 0 (read), PID = 36 (PWM)
	//PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PWM << PMC_PCR_PID_Pos);
	//PMC->PMC_PCER1 |= 1 << (ID_PWM - 32);
//
	//// enable PWM channels
	//PWM->PWM_ENA = PWM_ENA_CHID5 | PWM_ENA_CHID6;
//
	//// set PWM clock A to 1 MHz and clock B to 84 MHz
	//PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(DIVA);
	//PWM->PWM_CLK |= PWM_CLK_PREB(0) | PWM_CLK_DIVB(DIVB);
//
	//// assign clocks to respective channels: clock A for channel 5 (PIN45), clock B for channel 6 (PIN44)
	//// waveform set to be left-aligned
	//PWM->PWM_CH_NUM[WMH5].PWM_CMR = PWM_CMR_CPRE_CLKA;
	//PWM->PWM_CH_NUM[WMH6].PWM_CMR = PWM_CMR_CPRE_CLKB;
	//
	//// set PIN45 to a period to 20 ms, giving a frequency of 50 Hz
	//PWM->PWM_CH_NUM[WMH5].PWM_CPRD = PWM_CPRD_CPRD(CPRDA);
//
	//// set PIN44 to not initially have a pulse
	//PWM->PWM_CH_NUM[WMH6].PWM_CPRD = PWM_CPRD_CPRD(0);
//}
//
//
//void pwm_set_duty_cycle(float duty_cycle, unsigned int channel) {
	//if ((duty_cycle < 0) || (duty_cycle > 1)) {
		//return;
	//}
//
	//if (channel == WMH6 || channel == WMH5) {
		//int CDTY = 0;
		//CDTY = (int) (PWM->PWM_CH_NUM[channel].PWM_CPRD*(1 - duty_cycle));
		//PWM->PWM_CH_NUM[channel].PWM_CDTY = PWM_CDTY_CDTY(CDTY);
	//}
//}



void pwm_init() {
	// enable peripheral function B for PIN45 and PIN44
	PIOC->PIO_ABSR |= PIO_PC19B_PWMH5 ;

	// disable PIO from controlling PIN44 and PIN45
	PIOC->PIO_PDR |= PIO_PC19B_PWMH5;

	// enable clock for PWM:    DIV = 0 (clk = MCK), CMD = 0 (read), PID = 36 (PWM)
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PWM << PMC_PCR_PID_Pos);
	PMC->PMC_PCER1 |= 1 << (ID_PWM - 32);

	// enable PWM channels
	PWM->PWM_ENA = PWM_ENA_CHID5 | PWM_ENA_CHID6;

	// set PWM clock A to 1 MHz and clock B to 84 MHz
	PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(DIVA);
	PWM->PWM_CLK |= PWM_CLK_PREB(0) | PWM_CLK_DIVB(DIVB);

	// assign clocks to respective channels: clock A for channel 5 (PIN45), clock B for channel 6 (PIN44)
	// waveform set to be left-aligned
	PWM->PWM_CH_NUM[WMH5].PWM_CMR = PWM_CMR_CPRE_CLKA;
	
	
	// set PIN45 to a period to 20 ms, giving a frequency of 50 Hz
	PWM->PWM_CH_NUM[WMH5].PWM_CPRD = PWM_CPRD_CPRD(CPRDA);

	// set PIN44 to not initially have a pulse

}


void pwm_set_duty_cycle(float duty_cycle) {
	duty_cycle = duty_cycle < DUTY_CYCLE_MIN ? DUTY_CYCLE_MIN : duty_cycle;
	duty_cycle = duty_cycle > DUTY_CYCLE_MAX ? DUTY_CYCLE_MAX : duty_cycle;
	
	PWM->PWM_CH_NUM[5].PWM_CDTY = PWM_CDTY_CDTY( (int)(PWM->PWM_CH_NUM[5].PWM_CPRD*(1 - duty_cycle)) );
}
