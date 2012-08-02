project( CannyEdgeDetector )

cmake_minimum_required( VERSION 2.8 )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( CannyEdgeDetector CannyEdgeDetector.cpp )
target_link_libraries( CannyEdgeDetector ${OpenCV_LIBS} )
