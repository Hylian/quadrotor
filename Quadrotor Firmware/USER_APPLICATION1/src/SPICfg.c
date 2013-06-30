void spi_init_pins(void)
{
	ioport_configure_port_pin(&PORTC, PIN4_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	//ioport_configure_port_pin(&PORTC, PIN4_bm, IOPORT_PULL_UP | IOPORT_DIR_INPUT);
	ioport_configure_port_pin(&PORTC, PIN5_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	ioport_configure_port_pin(&PORTC, PIN6_bm, IOPORT_DIR_INPUT);
	ioport_configure_port_pin(&PORTC, PIN7_bm, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
}

void spi_init_module(void)
{
	struct spi_device spi_device_conf = {
		.id = IOPORT_CREATE_PIN(PORTC, 4)
	};

	spi_master_init(&SPIC);
	spi_master_setup_device(&SPIC, &spi_device_conf, SPI_MODE_0, 1000000, 0);
	spi_enable(&SPIC);
}

void spi_init(void)
{
	spi_init_pins();
	spi_init_module();
	
}