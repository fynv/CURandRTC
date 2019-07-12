cmake_minimum_required (VERSION 3.0)

SET(CMAKE_INSTALL_RPATH ../lib)

add_executable(test_rand test_rand.cpp)

if (WIN32) 
target_compile_definitions(test_rand PUBLIC THRUST_RTC_DLL_IMPORT CURAND_RTC_DLL_IMPORT)
endif()

target_link_libraries(test_rand ThrustRTC CURandRTC)

install(TARGETS test_rand RUNTIME DESTINATION test_cpp)

