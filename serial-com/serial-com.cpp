#include "serial-com.h"

  
    int open_serial_port(const char *portname, speed_t baudrate)
 
    {
        int fd;
        struct termios tty;
        char devname[20];

        // Loop through a list of possible port names
        for (int i = 0; i < 10; i++)
        {
            snprintf(devname, sizeof(devname), "%s%d", portname, i);
            fd = open(devname, O_RDWR | O_NOCTTY | O_NONBLOCK);
            if (fd >= 0)
            {
                // Set the serial port parameters
                tcgetattr(fd, &tty);
                tty.c_cflag &= ~(PARENB | CSTOPB);
                tty.c_cflag |= CS8;
                tty.c_iflag &= ~INPCK;
                tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
                tty.c_oflag &= ~OPOST;
                cfsetispeed(&tty, baudrate);
                cfsetospeed(&tty, baudrate);
                tcsetattr(fd, TCSANOW, &tty);
                return fd;
            }
        }

        // If no port is found, return an error
        fprintf(stderr, "Failed to open_port serial port %s\n", portname);
        return -1;
    
}

int open_port(SP, const char * path, speed_t baudrate, int blocking) {
        sp.file_handle = open(path, O_RDWR | O_NOCTTY | (blocking) ? O_NONBLOCK : 0);
        if (sp.file_handle >= 0) {

        }
        PRINT("Failed to open_port serial port %s\n", path);
        return -1;
}