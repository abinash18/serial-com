#include "serial-com.h"

int set_config(serial_port& sp, port_config pc)
{
	sp.config = pc;
	return 0;
}

int set_baudrate(serial_port& sp, int baudrate)
{
	sp.config.baudrate = baudrate;
	return 0;
}
