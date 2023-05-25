#include <stdio.h>
#include <string.h>

#define SP struct serial_port &sp

#define PRINT(fmt, ...)                          \
    do                                           \
    {                                            \
        if (DEBUG)                               \
            fprintf(stderr, fmt, ##__VA_ARGS__); \
    } while (0)

/**
 * @brief Boolean for easy types.
 */
enum BOOL
{
    TRUE = 1,
    FALSE = 0
};

// TODO: Save terminal config and reapply once port is closed
// TODO: Time outs.
// TODO: Read until
/**
 *
 * Defined interface
 * All return error codes, other return values are in parameters as refrences.
 *
 */

int open_serial_port(const char *portname, int baudrate);

int open_port(SP, const char *portname, int baudrate);

/**
 * @brief Close the provided port and free it.
 * @param Port struct to free
 * @return error code.
 */
int close_port(SP);

/**
 * @brief Checks if there is bytes waiting in input buffer.
 * @param Port to check.
 * @return Number of bytes waiting (>=0). or -1 if error.
 */
int input_waiting(SP);

void set_parity(SP, BOOL parity);

void set_stop_bits(SP, BOOL stop_bits);

void set_num_bits(SP, BOOL bits);

void set_flow_control(SP, BOOL flow_control);

void set_baudrate(SP, int baudrate);
