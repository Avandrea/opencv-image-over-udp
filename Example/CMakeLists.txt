cmake_minimum_required(VERSION 3.5)
project(udpSend)

set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )

set(SOURCES ../UDPSocket.cpp ../UDPSocket.h)

add_executable(udpSend main.cpp ${SOURCES})
target_link_libraries( udpSend ${OpenCV_LIBS} )
