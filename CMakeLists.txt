cmake_minimum_required(VERSION 3.17)
project(AnomalyDetector)

set(CMAKE_CXX_STANDARD 11)
add_executable(AnomalyDetector
        anomaly_detection_util.h
        anomaly_detection_util.cpp
        AnomalyDetector.h
        SimpleAnomalyDetector.h
        timeseries.h
        timeseries.cpp
        SimpleAnomalyDetector.cpp
        MainTrain.cpp
        HybridAnomalyDetector.cpp
        HybridAnomalyDetector.h
        minCircle.cpp
        minCircle.h
        CLI.h
        CLI.cpp
        server.h
        server.cpp
        commands.h)
