cmake_minimum_required(VERSION 2.6)

project(colorBeep2)

find_package(OpenCV REQUIRED)

add_executable(colorBeep2 colorBeep2.cpp)
target_link_libraries(colorBeep2 ${OpenCV_LIBS})

add_executable(captureExample captureExample.cpp)
target_link_libraries(captureExample ${OpenCV_LIBS})

add_executable(videoWriter videoWriter.cpp)
target_link_libraries(videoWriter ${OpenCV_LIBS})
