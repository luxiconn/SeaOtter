cmake_minimum_required(VERSION 3.8.0)
project(SeaOtter VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 14)
set(SFML_ROOT ${CMAKE_SOURCE_DIR}/lib/SFML-2.4.2)
set(CRYPTOPP_ROOT ${CMAKE_SOURCE_DIR}/lib/cryptopp-7.0.0)

include(CTest)
enable_testing()

add_library(SeaOtter 
  src/Core/Game.cpp
  src/Utility/DataSaver.cpp)

if (MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  target_compile_options(SeaOtter INTERFACE /W4)
else()
  target_compile_options(SeaOtter INTERFACE -Wall -Wextra -Wpedantic)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/lib/SFML-2.4.2/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(SeaOtter ${SFML_LIBRARIES} ${sFML_DEPENDENCIES})
endif()

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CRYPTOPP_ROOT}/include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
