cmake_minimum_required(VERSION 3.21)
project(activity_log_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =============================
# Applicazione principale
# =============================
add_executable(activity_log_cpp
        main.cpp
        Time.cpp
        Activity.cpp
        DailyLog.cpp
        Utils.cpp
        NcursesUI.cpp
        )

target_link_libraries(activity_log_cpp ncursesw)


# =============================
# Testing
# =============================
enable_testing()

add_subdirectory(external/googletest)

add_executable(activity_log_tests
        tests/test_all.cpp
        Time.cpp
        Activity.cpp
        DailyLog.cpp
        Utils.cpp
        )

target_link_libraries(activity_log_tests gtest_main)

include(GoogleTest)
gtest_discover_tests(activity_log_tests)
