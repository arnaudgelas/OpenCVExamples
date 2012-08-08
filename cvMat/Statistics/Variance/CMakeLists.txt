project( Variance )

cmake_minimum_required( VERSION 2.8 )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( Variance Variance.cpp )
target_link_libraries( Variance ${OpenCV_LIBS} )
