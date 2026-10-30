cmake_minimum_required(VERSION 3.25)
project(Library)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES
        src/Container.cpp
        include/Container.h
)

add_library(Library ${SOURCE_FILES})

#add 'include' directory with header files from 'Library' project to paths
target_include_directories(Library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#Unit Tests section

enable_testing()
find_package (Boost 1.71.0 CONFIGS COMPONENTS "unit_test_framework" REQUIRED)
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)
set(SOURCE_TEST_CONTAINER_FILES
        # add files if necessary
        test/master.cpp
        test/ContainerTest.cpp)
add_executable (ContainerTester ${SOURCE_TEST_CONTAINER_FILES})
# add library with tested claseses to then tester program if necessary
target_link_libraries (ContainerTester
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)
# additional parameters influence amount of details of generated report
add_test(TestContainer ContainerTester
        --report_level=detailed
        --log_level=all
        --color_output=yes
)

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION>)