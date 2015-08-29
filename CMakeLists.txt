cmake_minimum_required(VERSION 2.8.3)
project(roscpp14)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  roslint
  std_msgs
)

roslint_cpp()

catkin_package(
  CFG_EXTRAS roscpp14.cmake
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp
)

include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

include(${PROJECT_SOURCE_DIR}/cmake/roscpp14.cmake)

roslint_cpp(samples/listener.cpp samples/service_server.cpp include/roscpp14/ros.h test/test_roscpp14.cpp)
add_executable(listener samples/listener.cpp)
add_executable(service_server samples/service_server.cpp)

target_link_libraries(listener
  ${catkin_LIBRARIES}
  )

target_link_libraries(service_server
  ${catkin_LIBRARIES}
  )

install(TARGETS listener service_server
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)

if (CATKIN_ENABLE_TESTING)
  find_package(catkin REQUIRED COMPONENTS rostest roscpp)
  add_rostest_gtest(test_roscpp14 test/roscpp14.test test/test_roscpp14.cpp)
  target_link_libraries(test_roscpp14 ${catkin_LIBRARIES})
endif()
