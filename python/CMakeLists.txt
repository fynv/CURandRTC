cmake_minimum_required (VERSION 3.0)

project(PyCURandRTC)

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
api_CURandRTC.cpp
)

set (INCLUDE_DIR 
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
add_library(PyThrustRTC SHARED IMPORTED)
set_property(TARGET PyThrustRTC PROPERTY IMPORTED_LOCATION ../install/test_python/ThrustRTC/libPyThrustRTC.so)
endif()

SET(CMAKE_INSTALL_RPATH $ORIGIN/../ThrustRTC:.)

add_library (PyCURandRTC SHARED ${LIB_SOURCES} ${LIB_HEADERS} ${INTERNAL_HEADERS} ${SRC})


if (WIN32) 
target_compile_definitions(PyCURandRTC PRIVATE CURAND_RTC_DLL_EXPORT)
target_compile_definitions(PyCURandRTC PUBLIC THRUST_RTC_DLL_IMPORT)
endif()

target_link_libraries(PyCURandRTC PyThrustRTC)

add_dependencies(Run_PackHeaders PackHeaders)
add_dependencies(PyCURandRTC Run_PackHeaders)

IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX  ../install CACHE PATH "Install path" FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)


install(FILES ${LIB_HEADERS} DESTINATION include)

if (WIN32) 
install(TARGETS PyCURandRTC
		RUNTIME DESTINATION test_python/CURandRTC
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib 
		)
else()
install(TARGETS PyCURandRTC DESTINATION test_python/CURandRTC)
endif()

install(FILES CURandRTC/__init__.py DESTINATION test_python/CURandRTC)
install(FILES setup.py README.md DESTINATION test_python)

set(PYTHON_TEST
	test/test_rand.py
	test/test_rand2.py
)


set(INCLUDE_TESTS false CACHE BOOL "Include tests")

if (INCLUDE_TESTS)
install(FILES ${PYTHON_TEST} DESTINATION test_python )
endif()




