#include motor.h

//http://asf.atmel.com/docs/3.8.1/xmegaa/html/group__pwm__group.html#gac4fcf87938d24de42d63116127ae5542

/* PWM Config Structs */
struct pwm_config pwm_cfg_D0;
struct pwm_config pwm_cfg_D1;
struct pwm_config pwm_cfg_E0;
struct pwm_config pwm_cfg_E1;

/* Initializes the PWM Config Structs */
void configPWM(void)
{
	sysclk_init(); //Start the system clock
	pwm_init(&pwm_cfg_D0, PWM_TCD0, PWM_CH_A, 400); //Configure for PWM on Pin D0 using channel A at 400 Hz
	pwm_init(&pwm_cfg_D1, PWM_TCD1, PWM_CH_B, 400);
	pwm_init(&pwm_cfg_E0, PWM_TCE0, PWM_CH_C, 400);
	pwm_init(&pwm_cfg_E1, PWM_TCE1, PWM_CH_D, 400);
}

void startPWM(void)
{
	pwm_start(pwm_cfg_D0, 50); //Start PWM on D0 with 50% duty cycle
	pwm_start(pwm_cfg_D1, 50);
	pwm_start(pwm_cfg_E0, 50);
	pwm_start(pwm_cfg_E1, 50);
}

/* Adjusts the duty cycle for a given PWM channel */
void setMotorSpeed(char motor, char speed)
{
	if(speed > 100)
		speed = 100;
	else if(speed < 0)
		speed = 0;
	switch(motor)
	{
		case MotorD0:
			pwm_set_duty_cycle_percent(&pwm_cfg_D0, speed);
			break;
		case MotorD1:
			pwm_set_duty_cycle_percent(&pwm_cfg_D1, speed);
			break;
		case MotorE0:
			pwm_set_duty_cycle_percent(&pwm_cfg_E0, speed);
			break;
		case MotorE1:
			pwm_set_duty_cycle_percent(&pwm_cfg_E1, speed);
			break;
		default:
	}
}