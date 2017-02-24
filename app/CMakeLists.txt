# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

set(libs_dir ${CMAKE_SOURCE_DIR}/libs)
include_directories(${libs_dir}/include/)



# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             src/main/cpp/native-lib.cpp )


add_library(avcodec-lib SHARED IMPORTED)
set_target_properties(avcodec-lib PROPERTIES IMPORTED_LOCATION ${libs_dir}/${ANDROID_ABI}/libavcodec-57.so)

add_library(avdevice-lib SHARED IMPORTED)
set_target_properties(avdevice-lib PROPERTIES IMPORTED_LOCATION ${libs_dir}/${ANDROID_ABI}/libavdevice-57.so)

add_library(avfilter-lib SHARED IMPORTED)
set_target_properties(avfilter-lib PROPERTIES IMPORTED_LOCATION ${libs_dir}/${ANDROID_ABI}/libavfilter-6.so)

add_library(avformat-lib SHARED IMPORTED)
set_target_properties(avformat-lib PROPERTIES IMPORTED_LOCATION ${libs_dir}/${ANDROID_ABI}/libavformat-57.so)

add_library(avutil-lib SHARED IMPORTED)
set_target_properties(avutil-lib PROPERTIES IMPORTED_LOCATION ${libs_dir}/${ANDROID_ABI}/libavutil-55.so)

add_library(libswscale-lib SHARED IMPORTED)
set_target_properties(libswscale-lib PROPERTIES IMPORTED_LOCATION ${libs_dir}/${ANDROID_ABI}/libswscale-4.so)

add_library(libswresample-lib SHARED IMPORTED)
set_target_properties(libswresample-lib PROPERTIES IMPORTED_LOCATION ${libs_dir}/${ANDROID_ABI}/libswresample-2.so)

add_library(ffmpeg_mod SHARED
   ${libs_dir}/include/cmdutils.c
   ${libs_dir}/include/ffmpeg_opt.c
   ${libs_dir}/include/ffmpeg_filter.c
   ${libs_dir}/include/ffmpeg.c
 )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because system libraries are included in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.
target_link_libraries( # Specifies the target library.
                       ffmpeg_mod
                       avdevice-lib
                       avcodec-lib
                       avfilter-lib
                       avformat-lib
                       avutil-lib
                       libswscale-lib
                       libswresample-lib
                       # Links the target library to the log library
                       # included in the NDK.
                    )

target_link_libraries( # Specifies the target library.
                       native-lib
                       ffmpeg_mod
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
