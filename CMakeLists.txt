cmake_minimum_required(VERSION 3.17)
project(FlightSimulator)

set(CMAKE_CXX_STANDARD 11)

add_executable(FlightSimulator main.cpp anomaly_detection_util.cpp anomaly_detection_util.h AnomalyDetector.h timeseries.h SimpleAnomalyDetector.h timeseries.cpp SimpleAnomalyDetector.cpp MainTrain.cpp)