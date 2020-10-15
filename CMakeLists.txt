cmake_minimum_required(VERSION 3.17)
project(FlightSimulator)

set(CMAKE_CXX_STANDARD 11)

add_executable(FlightSimulator main.cpp anomaly_detection.cpp anomaly_detection.h)