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

/**
* Op
*/
int open_port(SP, const char *portname, speed_t baudrate, int blocking);

/**
 * @brief Close the provided port and free it.
 * @param Port struct to free
 * @return error code.
 */
int close(SP);

/**
 * @brief Checks if there is bytes waiting in input buffer.
 * @param Port to check.
 * @return Number of bytes waiting (>=0). or -1 if error.
 */
int input_waiting(SP);