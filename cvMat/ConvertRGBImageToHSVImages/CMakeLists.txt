project( ConvertRGBImageToHSVImages )

cmake_minimum_required( VERSION 2.8 )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( ConvertRGBImageToHSVImages ConvertRGBImageToHSVImages.cpp )
target_link_libraries( ConvertRGBImageToHSVImages ${OpenCV_LIBS} )
