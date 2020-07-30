cmake_minimum_required(VERSION 2.8.11)
project(CALIB_CAM)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -v")

find_package(OpenCV REQUIRED)
include_directories($(OpenCV_INCLUDE_DIRS))

add_executable(calibrate calib_intrinsic.cpp popt_pp.h)
target_link_libraries(calibrate ${OpenCV_LIBS} "-lpopt")

add_executable(calibrate_right calib_intrinsic_right.cpp popt_pp.h)
target_link_libraries(calibrate_right ${OpenCV_LIBS} "-lpopt")


add_executable(read read_images.cpp)
target_link_libraries(read ${OpenCV_LIBS} "-lpopt")

add_executable(calibrate_stereo calib_stereo.cpp)
target_link_libraries(calibrate_stereo ${OpenCV_LIBS} "-lpopt")

add_executable(undistort_rectify undistort_rectify.cpp)
target_link_libraries(undistort_rectify ${OpenCV_LIBS} "-lpopt")

add_executable(camera_test camera_test.cpp)
target_link_libraries(camera_test ${OpenCV_LIBS} "-lpopt")

add_executable(rescale rescale.cpp)
target_link_libraries(rescale ${OpenCV_LIBS} "-lpopt")

add_executable(main main.cpp)
target_link_libraries(main ${OpenCV_LIBS} "-lpopt")
