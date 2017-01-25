cmake_minimum_required(VERSION 3.6)
project(ex3)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES Driver.cpp Driver.h LuxuryCab.cpp LuxuryCab.h MainFlow.cpp MainFlow.h Passenger.cpp Passenger.h StandardCab.cpp StandardCab.h TaxiCab.cpp TaxiCab.h TaxiCenter.cpp TaxiCenter.h Trip.cpp Trip.h Point.cpp Point.h GridPoint.cpp GridPoint.h bfs.cpp bfs.h Grid.cpp Grid.h Obstacle.cpp Obstacle.h test/tripTest.cpp test/driverTest.cpp test/gtest.cpp test/taxiCenterTest.cpp Socket.cpp Socket.h Socket.cpp Socket.h client.cpp client.h Udp.cpp Udp.h Tcp.h Tcp.cpp ThreadPool.h ThreadPool.cpp)
add_executable(ex3 ${SOURCE_FILES})
target_link_libraries(ex3 gtest gtest_main ${Boost_LIBRARIES})