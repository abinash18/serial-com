if(${CMAKE_SYSTEM_NAME} MATCHES "Linux") 
    set(SOURCES serial-com-linux.h serial-com-linux.cpp)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(SOURCES serial-com-windows.h serial-com-windows.cpp)
endif()

# Here I add the required source and header files for my library.
# I can add more source files if needed here
add_library(
    SERIAL_COM STATIC # The library name is libSERIAL_INTERFACE and it is compiled as a shared object (.so)
    serial-com.h  
    ${SOURCES}
)
target_include_directories(SERIAL_COM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(SERIAL_COM PROPERTIES CMAKE_POSITION_INDEPENDENT_CODE ON)

# Link the serial library to my library
# Since i am compiling libCANBUS_INTERFACE as a seperate library i need to link
# any used ones into that rather than this project. since i am only using it for testing.
# target_link_libraries(SERIAL_COM serialport)