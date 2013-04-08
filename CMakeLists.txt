cmake_minimum_required(VERSION 2.6)

project(eyeborg)

find_package(OpenCV REQUIRED)

add_executable(eyeborg eyeborg_norec.cpp)
target_link_libraries(eyeborg ${OpenCV_LIBS})

add_executable(webcam webcam.cpp)
target_link_libraries(webcam ${OpenCV_LIBS})
