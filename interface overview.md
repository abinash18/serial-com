# Method definitions

Methods all return an integer error code. no function will handle errors. Rather it will return error code and then another function will take that error code and return the error description.

Cpp and polymorphism pardigms will not be used to lessen overhead.
although code will be written in Cpp but surrounded with ``` extern "C" {}```

file handle will be stored in a structure object.

```C 

struct serial_port {
    int file_handle = -1; // Initialization Check when first created.
    int mode; // Bit field. i forgor how to define it 💀
    int port_data ...; // Let all the data like model and connection interface and stuff like that define here.
}
/**
 * Pass a refrence to the serial port structure, therefore the user has to create it before opening.
 */
int serial_open(struct serial_port & sp, const char * port_address) {
    return error_code;
}
```

There can be methods like:
1. open
2. close
3. get error
4. 



Error codes:
- -2 file not found / port not open