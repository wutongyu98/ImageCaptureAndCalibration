project(main)
 
cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)
find_package(OpenCV REQUIRED)


pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0 gstreamer-app-1.0 gstreamer-video-1.0)
pkg_check_modules(TCAMLIB tcam)

message( ${TCAMLIB_LIBRARIES})

include_directories( ${CMAKE_CURRENT_BINARY_DIR}  ${GSTREAMER_INCLUDE_DIRS} ${TCAM_INCLUDE_DIRS}  ${OpenCV_INCLUDE_DIRS} )
add_definitions(${GSTREAMER_CFLAGS_OTHER})

add_executable( main 
                src/talker.cpp 
                src/tcamimage.cpp 
                src/tcamcamera.cpp
                src/tcam_image_reader.cpp
#                 src/file_image_reader.cpp
                src/tcam_image_reader.h
                src/tcamprop.h
                src/file_image_reader.h
                src/image_reader.h
                src/tcamcamera.h
                src/tcamimage.h
                src/input_arg_parser.h
                )

target_link_libraries(main ${TCAMLIB_LIBRARIES} ${GSTREAMER_LIBRARIES} ${OpenCV_LIBS} )

