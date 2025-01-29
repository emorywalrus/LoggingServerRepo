cmake_minimum_required(VERSION 3.5.0)
project(LoggingServer VERSION 0.1.0 LANGUAGES C CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

qt_standard_project_setup()

qt_add_executable(LoggingServer main.cpp logging_server.h)

target_link_libraries(LoggingServer PRIVATE Qt6::Core Qt6::Network)

