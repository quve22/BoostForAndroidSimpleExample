cmake_minimum_required(VERSION 3.4.1)

############### Boost ###############

set(BOOST_ROOT ${PROJECT_SOURCE_DIR}/src/main/3rdparty/boost)
set(BOOST_LIBS_PATH ${BOOST_ROOT}/lib/${ANDROID_ABI}/lib)
set(BOOST_INC_PATH ${BOOST_ROOT}/include)

file(GLOB BOOST_LIBS ${BOOST_LIBS_PATH}/*.a)

include_directories(${BOOST_INC_PATH})

#####################################

add_library(native-lib SHARED src/main/cpp/native-lib.cpp)

find_library(log-lib log)

target_link_libraries(native-lib
                      ${BOOST_LIBS}     ### Link boost libraries
                      ${log-lib})