project( OpenCVExamples )

cmake_minimum_required( VERSION 2.8 )

find_package( OpenCV REQUIRED )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${OpenCVExamples_BINARY_DIR}/bin
)

add_subdirectory( GetImageSize )
add_subdirectory( DisplayAnImage )
add_subdirectory( ConvertRGBImageToHSVImages )
add_subdirectory( ConvertRGBImageToYCbCrImages )
add_subdirectory( KMeansOnRGBImage )
