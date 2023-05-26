#include "serial-com-linux.h"

/**
 * struct termios
 * 	tcflag_t c_iflag;	 	input mode flags
 * 	tcflag_t c_oflag;		output mode flags
 * 	tcflag_t c_cflag;		control mode flags
 * 	tcflag_t c_lflag;		local mode flags
 * 	cc_t c_line;			line discipline
 * 	cc_t c_cc[NCCS];		control characters
 *
 */

int open_port(SP, const char* path, speed_t baudrate, int blocking)
{
	if (sp.file_handle != -1)
	{
		PRINT("Port struct already in use and not ready. Close port before reusing config.");
		return -1;
	}
	sp.file_handle = open(path, O_RDWR | O_NOCTTY | (blocking) ? O_NONBLOCK : 0);
	if (sp.file_handle >= 0)
	{
		struct termios tty;
		// Set the serial port parameters
		tcgetattr(sp.file_handle, &tty);

		if (sp.parity)
			tty.c_cflag &= ~PARENB;
		else
			tty.c_cflag |= PARENB;

		if (sp.two_stop_bits)
			tty.c_cflag |= CSTOPB;
		else
			tty.c_cflag &= ~CSTOPB;

		switch (sp.num_bits)
		{
		case 5:
			tty.c_cflag |= CS5;
			break;
		case 6:
			tty.c_cflag |= CS6;
			break;
		case 7:
			tty.c_cflag |= CS7;
			break;
		case 8:
			tty.c_cflag |= CS8;
			break;
		default:
			tty.c_cflag |= CS8;
			break;
		}

		if (sp.flow_control)
			tty.c_cflag |= CRTSCTS;
		else
			tty.c_cflag &= ~CRTSCTS;

		tty.c_iflag &= ~INPCK;

		// disable software flow control
		tty.c_iflag &= ~(IXON | IXOFF | IXANY);

		// Disable input handling
		tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

		tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHONL | ISIG);

		// prevent output processing.
		tty.c_oflag &= ~OPOST;

		cfsetispeed(&tty, baudrate);
		cfsetospeed(&tty, baudrate);

		if (tcsetattr(sp.file_handle, TCSANOW, &tty) != 0)
		{
			PRINT("Error %i from tcsetattr: %s\n", errno, strerror(errno));
			return -1;
		}
		sp.baudrate = baudrate;

		return 0;
	}
	PRINT("Failed to open_port serial port %s\n", path);
	return -1;
}

int close_port(SP)
{
	if (sp.file_handle == -1)
	{
		PRINT("Port already closed.");
		return -1;
	}
	close(sp.file_handle);
	sp.file_handle = -1;
	return 0;
}

// https://man7.org/linux/man-pages/man2/ioctl.2.html
int input_waiting(SP)
{
	int bytes_waiting;
	// It returns -1 if error occured errno will indicate error.
	return ioctl(sp.file_handle, FIONREAD, &bytes_waiting);
}

void set_parity(SP, BOOL parity) {}

void set_stop_bits(SP, BOOL stop_bits) {}

void set_num_bits(SP, BOOL bits) {}

void set_flow_control(SP, BOOL flow_control) {}

void set_baudrate(SP, int baudrate) {}
