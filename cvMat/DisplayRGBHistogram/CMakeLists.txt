project( DisplayRGBHistogram )

cmake_minimum_required( VERSION 2.8 )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( DisplayRGBHistogram DisplayRGBHistogram.cpp )
target_link_libraries( DisplayRGBHistogram ${OpenCV_LIBS} )
