#pragma once

#include "serial-com.h"

#include <errno.h> // Error integer and strerror() function
#include <fcntl.h> // Contains file controls like O_RDWR
#include <sys/ioctl.h>
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()

