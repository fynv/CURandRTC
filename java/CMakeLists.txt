cmake_minimum_required (VERSION 3.0)

project(JCURandRTC)

find_package(JNI REQUIRED)
find_package(Java REQUIRED)
include(UseJava)

add_executable(PackHeaders ../internal/pack_headers.cpp)
add_custom_target(Run_PackHeaders
COMMAND PackHeaders
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..
COMMENT "Running PackHeaders in ${CMAKE_CURRENT_SOURCE_DIR}/.."
SOURCES ../internal/pack_headers.cpp
)


set(LIB_SOURCES
../internal/cuda_wrapper.cpp
../DVRNG.cpp
)

set(LIB_HEADERS
../CURandRTC_api.h
../curandrtc_built_in.h
../DVRNG.h
)

set(INTERNAL_HEADERS
../internal/cuda_wrapper.h
../internal/xor_wow_data.hpp
)

set (SRC
JCURandRTC_Native.h
JCURandRTC_Native.cpp
)

set (INCLUDE_DIR 
${JNI_INCLUDE_DIRS}
.
..
../internal
../install/include
)


if (WIN32) 
set (DEFINES  ${DEFINES}
-D"_CRT_SECURE_NO_DEPRECATE"  
-D"_SCL_SECURE_NO_DEPRECATE" 
-D"_CRT_SECURE_NO_WARNINGS"
)
else()
add_definitions(-std=c++14)
add_compile_options(-fPIC)
endif()

include_directories(${INCLUDE_DIR})
add_definitions(${DEFINES})

if (WIN32) 
link_directories(../install/lib)
else()
link_directories(../install/test_java)
endif()

SET(CMAKE_INSTALL_RPATH .)

add_library (JCURandRTC_Native SHARED ${LIB_SOURCES} ${LIB_HEADERS} ${INTERNAL_HEADERS} ${SRC})

if (WIN32) 
target_compile_definitions(JCURandRTC_Native PRIVATE CURAND_RTC_DLL_EXPORT)
target_compile_definitions(JCURandRTC_Native PUBLIC THRUST_RTC_DLL_IMPORT)
endif()
target_link_libraries(JCURandRTC_Native JThrustRTC_Native)

add_dependencies(Run_PackHeaders PackHeaders)
add_dependencies(JCURandRTC_Native Run_PackHeaders)

IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX  ../install CACHE PATH "Install path" FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

install(FILES ${LIB_HEADERS} DESTINATION include)

if (WIN32) 
install(TARGETS JCURandRTC_Native 
		RUNTIME DESTINATION test_java
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib 
		)
else()
install(TARGETS JCURandRTC_Native DESTINATION test_java)
endif()

##################################################

set(CMAKE_JAVA_INCLUDE_PATH ../install/test_java/JThrustRTC.jar)

set(JAVA
Native.java
DVRNG.java
)

add_jar(JCURandRTC ${JAVA})
install_jar(JCURandRTC test_java)

##################################################

set(BUILD_TESTS false CACHE BOOL "Build tests")

if (BUILD_TESTS)
add_subdirectory(test)
endif()

