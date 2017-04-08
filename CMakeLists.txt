cmake_minimum_required(VERSION 3.7)
project(asio_example)

set(CMAKE_CXX_STANDARD 11)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.63.0 REQUIRED COMPONENTS system thread regex context)
IF(Boost_FOUND)
     message(${Boost_LIBRARY_DIRS})
     INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
     LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

set(SOURCE_FILES
        async_timer.cpp
        sync_timer.cpp)

set(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_CONTEXT_LIBRARY})
add_executable(sync_timer sync_timer.cpp)
target_link_libraries(sync_timer ${USED_LIBS})
add_executable(async_timer async_timer.cpp)
target_link_libraries(async_timer ${USED_LIBS})