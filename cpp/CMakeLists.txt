cmake_minimum_required (VERSION 3.0)

project(CURandRTC)

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

set (INCLUDE_DIR
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
link_directories(../install/lib)
add_definitions(${DEFINES})

SET(CMAKE_INSTALL_RPATH $ORIGIN/.:.)

add_library(CURandRTC SHARED ${LIB_SOURCES} ${LIB_HEADERS} ${INTERNAL_HEADERS})

if (WIN32) 
target_compile_definitions(CURandRTC PRIVATE CURAND_RTC_DLL_EXPORT)
target_compile_definitions(CURandRTC PUBLIC THRUST_RTC_DLL_IMPORT)
endif()
target_link_libraries(CURandRTC ThrustRTC)

add_dependencies(Run_PackHeaders PackHeaders)
add_dependencies(CURandRTC Run_PackHeaders)

IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX  ../install CACHE PATH "Install path" FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

install(FILES ${LIB_HEADERS} DESTINATION include)

if (WIN32) 
install(TARGETS CURandRTC 
		RUNTIME DESTINATION test_cpp
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib 
		)
else()
install(TARGETS CURandRTC DESTINATION lib)
endif()


set(BUILD_TESTS false CACHE BOOL "Build tests")

if (BUILD_TESTS)
add_subdirectory(test)
endif()
