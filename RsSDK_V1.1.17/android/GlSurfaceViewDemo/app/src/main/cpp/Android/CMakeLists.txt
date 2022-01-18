# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# configure import libs
set(distribution_DIR ${CMAKE_SOURCE_DIR}/../../../../../distribution)

add_library(lib_RSNet SHARED IMPORTED)
set_target_properties(lib_RSNet PROPERTIES IMPORTED_LOCATION
    ${distribution_DIR}/RSNet/Lib/${ANDROID_ABI}/libRSNet.so)

add_library(lib_RSPlay SHARED IMPORTED)
set_target_properties(lib_RSPlay PROPERTIES IMPORTED_LOCATION
    ${distribution_DIR}/RSPlay/Lib/${ANDROID_ABI}/libRSPlay.so)

add_library(lib_Bugly SHARED IMPORTED)
set_target_properties(lib_Bugly PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/Lib/${ANDROID_ABI}/libBugly.so)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

file(GLOB SOURCES
    "../DeviceManager/*.cpp"
    "../Include/*.cpp"
    "../JsonCpp/*.cpp"
    "../Paramers/base64.cpp"
    "../Paramers/ParamBase.cpp"
    "../Paramers/ChLive.cpp"
    "../Paramers/RSPush.cpp"
    "../Paramers/SysParamDst.cpp"
    "../Paramers/AlarmPIR.cpp"
    "../Paramers/LiveParam.cpp"
    "../Paramers/FloodLight.cpp"
    "../Paramers/AlarmIO.cpp"
    "../Paramers/AlarmNewIO.cpp"
    "../Paramers/SysInfHdd.cpp"
    "../Paramers/NetBase.cpp"
    "../Paramers/AlarmMotion.cpp"
    "../Paramers/RSPushSubscription.cpp"
    "../Paramers/RecPlan.cpp"
    "../Paramers/SysInfBase.cpp"
    "../Paramers/IPCSet.cpp"
    "../Paramers/RecPlanIPC.cpp"
    "../Paramers/EncodeStream.cpp"
    "../Paramers/AlarmEncode.cpp"
    "../Paramers/JsonPage.cpp"
    "../Paramers/ChLive.cpp"
    "../Paramers/base64.cpp"
    "../Paramers/SysParamUSer.cpp"
    "../Paramers/NewNetEmail.cpp"
    "../Paramers/SwannCloSto.cpp"
    "../Paramers/DropboxParam.cpp"
    "*.cpp"
    "../Remote/ParamRemoteTest.cpp"
)

add_library(SDKWrapper SHARED ${SOURCES})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

target_include_directories(SDKWrapper PRIVATE
                           ${distribution_DIR}/RSNet/Include
                           ${distribution_DIR}/RSPlay/Include)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       SDKWrapper
                       lib_RSNet
                       lib_RSPlay
                       lib_Bugly
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib})

add_custom_command(TARGET SDKWrapper PRE_BUILD
                   COMMAND "${CMAKE_COMMAND}" -E
                   copy
                   #"${distribution_DIR}/RSNet/Lib/${ANDROID_ABI}/libP2PClient.so"
                   "${distribution_DIR}/RSNet/Lib/${ANDROID_ABI}/libP2PTunnelAPIs.so"
                   "${distribution_DIR}/RSNet/Lib/${ANDROID_ABI}/libt2u.so"
                   "${distribution_DIR}/RSNet/Lib/${ANDROID_ABI}/libRSNet.so"
                   "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")


add_custom_command(TARGET SDKWrapper PRE_BUILD
                   COMMAND "${CMAKE_COMMAND}" -E
                   copy
                   "${distribution_DIR}/RSPlay/Lib/${ANDROID_ABI}/libRSPlay.so"
                   "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

add_custom_command(TARGET SDKWrapper PRE_BUILD
                  COMMAND "${CMAKE_COMMAND}" -E
                  copy
                  "${CMAKE_SOURCE_DIR}/Lib/${ANDROID_ABI}/libBugly.so"
                  "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
