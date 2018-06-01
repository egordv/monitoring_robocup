cmake_minimum_required(VERSION 2.8)
project(monitoring_robocup)

find_package(
    catkin REQUIRED COMPONENTS
    rhoban_utils rhoban_geometry robocup_referee rhoban_team_play sfml
)

catkin_package(
    INCLUDE_DIRS .
    CATKIN_DEPENDS rhoban_utils rhoban_geometry robocup_referee rhoban_team_play sfml
)

#Camera options
option (USE_CAMERA "Use external camera" ON)

#Camera to use (index in /dev/videoX)
set (CAMERA "1" CACHE STRING "Camera to use")

include_directories(${catkin_INCLUDE_DIRS})

#Enable C++11
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#Enable real warnings
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")

set (LIBRARIES ${catkin_LIBRARIES})

if (USE_CAMERA)
    set (OpenCV_DIR "/home/gregwar/opencv/build")
    find_package(OpenCV REQUIRED)
    include_directories(${OpenCV_DIR}/include)
    include_directories(${OpenCV_DIR}/include/opencv2)
    set (LIBRARIES ${LIBRARIES} ${OpenCV_LIBS})

    add_definitions (-DUSE_CAMERA)
    add_definitions (-DCAMERA=${CAMERA})
endif ()

add_executable(MonitoringRoboCup
    RichText.cpp
    monitoring.cpp
    log.cpp
)
target_link_libraries(MonitoringRoboCup
    ${LIBRARIES}
    pthread
)

set(BINARY_FILES
  font.ttf
  RhobanFootballClub.png)

file(COPY ${BINARY_FILES}
  DESTINATION ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_BIN_DESTINATION}/
  )
