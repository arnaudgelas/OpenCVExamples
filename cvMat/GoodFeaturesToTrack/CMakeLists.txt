project( GoodFeaturesToTrack )

cmake_minimum_required( VERSION 2.8 )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( GoodFeaturesToTrack GoodFeaturesToTrack.cpp )
target_link_libraries( GoodFeaturesToTrack ${OpenCV_LIBS} )
