#pragma once

#include "serial-com.h"

#include <errno.h> // Error integer and strerror() function
#include <fcntl.h> // Contains file controls like O_RDWR
#include <sys/ioctl.h>
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()

struct serial_port
{
    int file_handle = -1; // handle to the port.
    int mode = 0;
    char *path; // Physical system path of com port
    struct termios tty;
    int baudrate;

    BOOL parity = FALSE,
         /** If TRUE two stop bits are used, if FALSE only one is used*/
        two_stop_bits = FALSE;
    /** Number bits 5 6 7 or 8 */
    int num_bits = 8;

    BOOL flow_control = FALSE;
};