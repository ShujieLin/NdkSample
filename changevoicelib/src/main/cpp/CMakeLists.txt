# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

#导入头文件
include_directories("inc")

project("changevoicelib")

#批量导入所有源文件
file(GLOB allCPP *.c *.h *.cpp)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
add_library( # Sets the name of the library.
        changevoicelib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${allCPP})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.


# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

# 导入库文件
# CMAKE_SOURCE_DIR == CMakeLists.txt所在的路径
# CMAKE_ANDROID_ARCH_ABI 当前设备的cpu架构
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}")

target_link_libraries( # Specifies the target library.
        changevoicelib

        # Links the target library to the log library
        # included in the NDK.
        log #自动查找指定的库，链接到lbndksample.so里面去
        fmod
        fmodL)