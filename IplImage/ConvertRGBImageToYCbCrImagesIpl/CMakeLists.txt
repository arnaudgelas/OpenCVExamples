project( ConvertRGBImageToYCbCrImagesIpl )

cmake_minimum_required( VERSION 2.8 )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( ConvertRGBImageToYCbCrImagesIpl ConvertRGBImageToYCbCrImages.cpp )
target_link_libraries( ConvertRGBImageToYCbCrImagesIpl ${OpenCV_LIBS} )
