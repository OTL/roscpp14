if (APPLE)
else (APPLE)
  # for Ubuntu14.04
  # sudo add-apt-repository ppa:ubuntu-toolchain-r/test
  # sudo apt-get update
  # sudo apt-get install g++-4.9
  set(CMAKE_CXX_COMPILER g++-4.9)
endif (APPLE)
add_definitions(-std=c++14)
