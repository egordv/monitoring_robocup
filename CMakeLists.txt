cmake_minimum_required(VERSION 2.8)
project(MonitoringRoboCup)

find_package(
    catkin REQUIRED COMPONENTS
    RhobanUtils Eigen RhobanServer RobocupReferee
)

catkin_package(
    INCLUDE_DIRS .
    CATKIN_DEPENDS RhobanUtils RobocupReferee
)

include_directories(${catkin_INCLUDE_DIRS})

#Enable C++11
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#Enable real warnings
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")

#Include SFML (graphic library)
set(SFML_DIRECTORY "SFML" CACHE STRING "SFML lib directory")
include_directories(${SFML_DIRECTORY}/include)
link_directories(${SFML_DIRECTORY}/lib)
add_executable(MonitoringRoboCup
    monitoring.cpp
)
target_link_libraries(MonitoringRoboCup
    ${catkin_LIBRARIES}
    pthread
    sfml-graphics
    sfml-window
    sfml-system
    GL
    GLU
)

