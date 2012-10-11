cmake_minimum_required(VERSION 2.8)

project(StringReverser)

#create a library from our code
add_library(StringReverser src/StringReverser.cpp)

#setup testing environment
enable_testing()
set(GTEST_ROOT ${CMAKE_SOURCE_DIR}/../gtest-1.6.0)
link_directories(${GTEST_ROOT})
find_package(GTest REQUIRED)

#create a test executable linked to our code
include_directories(${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src)
add_executable(TestStringReverser test/TestStringReverser.cpp)
target_link_libraries(TestStringReverser StringReverser ${GTEST_MAIN_LIBRARY} ${GTEST_LIBRARIES} pthread)

#get boost
set(CUKE_CORE_BOOST_LIBS thread system regex date_time)
set(CUKE_DYNAMIC_BOOST_LIBS ${CUKE_CORE_BOOST_LIBS} ${CUKE_TEST_BOOST_LIBS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_ALL_DYN_LINK")
set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost COMPONENTS ${CUKE_DYNAMIC_BOOST_LIBS})
include_directories(${Boost_INCLUDE_DIRS})
set(CUKE_EXTRA_LIBRARIES ${CUKE_EXTRA_LIBRARIES} ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_DATE_TIME_LIBRARY})

#create the Cucumber wire-server to provied steps
set(CUKE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/../cucumber-cpp/include)
set(CUKE_LIBRARIES libcucumber-cpp.a)
link_directories(${CMAKE_SOURCE_DIR}/../cucumber-cpp/build/src)
include_directories(${CUKE_INCLUDE_DIRS})
add_executable(StringReverserSteps test/StringReverserSteps.cpp)
target_link_libraries(StringReverserSteps StringReverser ${GTEST_MAIN_LIBRARY} ${GTEST_LIBRARIES} pthread ${CUKE_LIBRARIES} ${CUKE_EXTRA_LIBRARIES})