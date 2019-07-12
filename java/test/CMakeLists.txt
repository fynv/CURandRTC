
find_package(Java REQUIRED)
include(UseJava)

set(CMAKE_JAVA_INCLUDE_PATH ../../install/test_java/JThrustRTC.jar)

add_jar(JCURandRTCTests SOURCES test_rand.java INCLUDE_JARS JCURandRTC)
install_jar(JCURandRTCTests test_java)

install(FILES run_tests.bat run_tests.sh DESTINATION test_java )
