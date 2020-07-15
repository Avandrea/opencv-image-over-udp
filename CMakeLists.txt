cmake_minimum_required(VERSION 3.0.0)
project(UDPSOCKET VERSION 0.1.0)

file(GLOB UDPSOCKET_SRC
    ./*.cpp
    )

add_library(udpsocket
            SHARED
            ${UDPSOCKET_SRC}  )

target_include_directories( udpsocket PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )