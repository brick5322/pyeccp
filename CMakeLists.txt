cmake_minimum_required(VERSION 3.21)
project(pyECCP C)

set(CMAKE_C_STANDARD 99)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

include_directories(/usr/include/python3.10 /usr/include/x86_64-linux-gnu/python3.10 ./includes)
link_libraries(m)
add_executable(pyECCP_test src/BMPcodec.c src/Camera.c ./src/main.c src/PyCameraObject.c src/PyECCP_Module.c src/stream.c test/test2_Camera.c test/test1_BMPcodec.c src/ECCP.c includes/ECCP.h test/test3_ECCP.c src/ECCP_code_func.c includes/ECCP_code_func.h)