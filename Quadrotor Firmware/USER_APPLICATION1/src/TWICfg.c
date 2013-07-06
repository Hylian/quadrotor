#include "TWICfg.h"

void twi_init(void)
{
	twi_master_options_t opt = {
		.speed = 50000,
		.chip  = 0x50
	};
	
	twi_master_setup(&TWIM0, &opt);
}