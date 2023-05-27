#include <serial-com-windows.h>

int open_port(SP, const char* port_path)
{
	if (sp.port_handle != -1)
	{
		PRINT("this config is already in use. ");
		return -1;
	}

	HANDLE com;

	com = CreateFileA(port_path, GENERIC_READ | GENERIC_WRITE,
	                  0,    // No Sharing / Blocking
	                  NULL, // No security
	                  OPEN_EXISTING,
	                  0, // No overlaped IO
	                  NULL);

	if (com == INVALID_HANDLE_VALUE)
	{
		PRINT("Failed to open_port serial port %s\n", port_path);
		return -1;
	}
	sp.port_handle = (uintptr_t)com;

	apply_config(sp);
	// TODO: Odd or nothing, in future make this applicable to all types of parity.

	PRINT("Opened port successfully. %s", port_path);
	return 0;
}

/**
 * Specific to windows. 
*/

int apply_config(SP)
{
	if (sp.port_handle == -1)
	{
		PRINT("Port not open, port must be open to apply config.");
		return -1;
	}
	DCB tty;                                    // Port control structure.
	GetCommState((HANDLE)sp.port_handle, &tty); // Retrieve the current structure.
	tty.BaudRate = sp.config.baudrate;
	tty.StopBits = (sp.config.two_stop_bits) ? 2 : 0; // win api is weird i didnt know u can have 1.5 stop bits.
	tty.Parity   = (sp.config.parity) ? 1 : 0;
	// TODO: Odd or nothing, in future make this applicable to all types of parity.

	SetCommState((HANDLE)sp.port_handle, &tty);

	return 0;
}

int close_port(SP)
{
	if (sp.port_handle == -1)
	{
		PRINT("Port already closed");
		return 0;
	}

	CloseHandle((HANDLE)sp.port_handle);
	// TODO: Check for errors here and return -1
	return 0;
}

// TODO: This is a hacky way i have no idea how to do this anyother way.

int input_waiting(SP)
{
	COMSTAT cs;
	DWORD   type;
	ClearCommError((HANDLE)sp.port_handle, &type, &cs);

	return cs.cbInQue;
}
