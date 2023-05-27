#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define PRINT(fmt, ...)                          \
	do                                           \
	{                                            \
		if (DEBUG)                               \
			fprintf(stderr, fmt, ##__VA_ARGS__); \
	} while (0)


struct port_config {
	int   mode = 0;
	char* path; // Physical system path of com port
	int   baudrate;
	bool  parity = false,
	      /** If TRUE two stop bits are used, if FALSE only one is used*/
	      two_stop_bits = false;
	/** Number bits 5 6 7 or 8 */
	int num_bits = 8;

	bool flow_control = false;

	bool blocking = false;
};

// Removed termios.
struct serial_port {
	// Having this as uintptr_t makes sure that whatever platform this runs on it always has enough space to store either a void* or a int.
	// Used for windows where it needs to store a HANDLE which is a pointer and on linux where it needs to store a int as a file handle.
	uintptr_t          port_handle = -1; // handle to the port.
	struct port_config config;
};


#define SP struct serial_port &sp
#define PC struct port_config pc


// TODO: Save terminal config and reapply once port is closed. because configs are presistant.
// TODO: Time outs.
// TODO: Read until
/**
 *
 * Defined interface
 * All return error codes, other return values are in parameters as refrences.
 *
 */

/**
 * @brief Opens a com port, uses the @link serial_port struct to apply settings and 
 * @param  
 * @param port_path 
 * @return 
*/
int open_port(SP, const char* port_path);

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

/**
 * @brief Apply the changed parameters in the config struct to the port.
 * @param sp the port to change
 * @return -1 if error. 0 if successful.
*/
int apply_config(SP);

/**
 * Individual set functions to change settings.
 * These are made for wrappers to use in python.
 * They will apply settings to the supplied port config struct.
 * You must call @link apply_config after changing these settings.
 */

// Why am i doing this?. well because i intend to make a wrapper for this library in python
// and in python i dont want to make a wrapper for the struct so im making getters and setters
// it makes it easier for people to get and set configs and use the library.

/**
 * @brief Sets a new config to a port struct dose not apply.
 * @param  
 * @param  
 * @return 
*/
int set_config(SP, PC);

/**
 * @brief Sets the new baudrate in a already created port config, the port dose not have to be open.
 * @param  
 * @param baudrate 
 * @return 
*/
int set_baudrate(PC, int baudrate);
