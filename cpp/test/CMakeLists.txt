cmake_minimum_required (VERSION 3.0)

SET(CMAKE_INSTALL_RPATH ../lib)

add_executable(test_rand test_rand.cpp)
add_executable(test_rand2 test_rand2.cpp)

if (WIN32) 
target_compile_definitions(test_rand PUBLIC THRUST_RTC_DLL_IMPORT CURAND_RTC_DLL_IMPORT)
target_compile_definitions(test_rand2 PUBLIC THRUST_RTC_DLL_IMPORT CURAND_RTC_DLL_IMPORT)
endif()

target_link_libraries(test_rand ThrustRTC CURandRTC)
target_link_libraries(test_rand2 ThrustRTC CURandRTC)

install(TARGETS test_rand RUNTIME DESTINATION test_cpp)
install(TARGETS test_rand2 RUNTIME DESTINATION test_cpp)

