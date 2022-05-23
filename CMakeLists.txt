cmake_minimum_required(VERSION 3.21)
project(pyECCP C)

set(CMAKE_C_STANDARD 99)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

include_directories(/usr/include/python3.10 /usr/include/x86_64-linux-gnu/python3.10 ./includes)

link_libraries(python3.10 m)
add_executable(pyECCP_test1  src/List.c src/Node.c src/BMPcodec.c src/Camera.c src/PyCameraObject.c src/stream.c src/ECCP.c src/ECCP_code_func.c includes/ECCP_code_func.h src/ECCP_event.c includes/ECCP_event.h src/ECCP_net.c includes/ECCP_net.h src/PyCamera.c test/test1_BMPcodec.c       )
add_executable(pyECCP_test2  src/List.c src/Node.c src/BMPcodec.c src/Camera.c src/PyCameraObject.c src/stream.c src/ECCP.c src/ECCP_code_func.c includes/ECCP_code_func.h src/ECCP_event.c includes/ECCP_event.h src/ECCP_net.c includes/ECCP_net.h src/PyCamera.c test/test2_Camera.c         )
add_executable(pyECCP_test3  src/List.c src/Node.c src/BMPcodec.c src/Camera.c src/PyCameraObject.c src/stream.c src/ECCP.c src/ECCP_code_func.c includes/ECCP_code_func.h src/ECCP_event.c includes/ECCP_event.h src/ECCP_net.c includes/ECCP_net.h src/PyCamera.c test/test3_ECCP.c           )
add_executable(pyECCP_test4  src/List.c src/Node.c src/BMPcodec.c src/Camera.c src/PyCameraObject.c src/stream.c src/ECCP.c src/ECCP_code_func.c includes/ECCP_code_func.h src/ECCP_event.c includes/ECCP_event.h src/ECCP_net.c includes/ECCP_net.h src/PyCamera.c test/test4_ECCP_code_func.c )
add_executable(pyECCP_test5  src/List.c src/Node.c src/BMPcodec.c src/Camera.c src/PyCameraObject.c src/stream.c src/ECCP.c src/ECCP_code_func.c includes/ECCP_code_func.h src/ECCP_event.c includes/ECCP_event.h src/ECCP_net.c includes/ECCP_net.h src/PyCamera.c test/test5_EventQueue.c     )
add_executable(pyECCP_test6s src/List.c src/Node.c src/BMPcodec.c src/Camera.c src/PyCameraObject.c src/stream.c src/ECCP.c src/ECCP_code_func.c includes/ECCP_code_func.h src/ECCP_event.c includes/ECCP_event.h src/ECCP_net.c includes/ECCP_net.h src/PyCamera.c test/test6_net_server.c)
add_executable(pyECCP_test6c src/List.c src/Node.c src/BMPcodec.c src/Camera.c src/PyCameraObject.c src/stream.c src/ECCP.c src/ECCP_code_func.c includes/ECCP_code_func.h src/ECCP_event.c includes/ECCP_event.h src/ECCP_net.c includes/ECCP_net.h src/PyCamera.c test/test6_net_client.c)
add_executable(pyECCP_testt1 src/List.c src/Node.c src/BMPcodec.c src/Camera.c src/PyCameraObject.c src/stream.c src/ECCP.c src/ECCP_code_func.c includes/ECCP_code_func.h src/ECCP_event.c includes/ECCP_event.h src/ECCP_net.c includes/ECCP_net.h src/PyCamera.c test/temp_test1.c           )