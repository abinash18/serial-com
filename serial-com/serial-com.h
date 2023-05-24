#include <stdio.h>
#include <string.h>

#include <errno.h>   // Error integer and strerror() function
#include <fcntl.h>   // Contains file controls like O_RDWR
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()

#define SP struct serial_port &sp

#define PRINT(fmt, ...)                          \
    do                                           \
    {                                            \
        if (DEBUG)                               \
            fprintf(stderr, fmt, ##__VA_ARGS__); \
    } while (0)

struct serial_port
{
    int file_handle = -1; // handle to the port.
    int mode = 0;
    char *path; // Physical system path of com port
};

/**
 *
 * Defined interface
 * All return error codes, other return values are in parameters as refrences.
 *
 */

int open_serial_port(const char *portname, speed_t baudrate);
