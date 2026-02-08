cmake_minimum_required(VERSION 3.21)
project(activity_log_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(activity_log_cpp
        main.cpp
        Time.cpp
        Activity.cpp
        DailyLog.cpp
        Utils.cpp
        )
