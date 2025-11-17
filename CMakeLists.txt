cmake_minimum_required(VERSION 3.22.1)
project(ceres_demo)

set(CMAKE_CXX_STANDARD 14)

find_package(Ceres REQUIRED)

include_directories(${CERES_INCLUDE_DIRS})

add_executable(helloworld src/helloworld.cc)
target_link_libraries(helloworld ${CERES_LIBRARIES})

add_executable(helloworld_analytic src/helloworld_analytic_diff.cc)
target_link_libraries(helloworld_analytic ${CERES_LIBRARIES})

add_executable(powell src/powell.cc)
target_link_libraries(powell ${CERES_LIBRARIES})