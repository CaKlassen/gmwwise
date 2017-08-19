cmake_minimum_required(VERSION 3.7)
project(GMWwise)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(
        "."
        "${CMAKE_CURRENT_SOURCE_DIR}/../Shared"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../../Wwise/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../../Wwise/samples/SoundEngine/Common"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../../Wwise/samples/SoundEngine/POSIX")

file(GLOB SOURCE_FILES ../Shared/*.cpp)
file(GLOB WWISE_COMMON ${CMAKE_CURRENT_SOURCE_DIR}/../../../../Wwise/samples/SoundEngine/Common/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../../Wwise/samples/SoundEngine/Common/*.inl)
file(GLOB WWISE_POSIX ${CMAKE_CURRENT_SOURCE_DIR}/../../../../Wwise/samples/SoundEngine/POSIX/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../../Wwise/samples/SoundEngine/POSIX/*.inl)

# Define build configuration pre-processor macros
set(CMAKE_CXX_FLAGS "-m32 ${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "-m32 ${CMAKE_C_FLAGS}")

if(${CMAKE_BUILD_TYPE} STREQUAL "Profile")
    add_definitions(-DDEBUG=1)
    set(LIB_NAME "GMWwise_profile")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_definitions(-DAK_OPTIMIZED)
    set(LIB_NAME "GMWwise")
endif()

link_directories("../../../../Wwise/Linux_x32/${CMAKE_BUILD_TYPE}/lib")
link_directories("../../../../Wwise/Linux_x32/${CMAKE_BUILD_TYPE}/bin")

add_library(${LIB_NAME} SHARED ${SOURCE_FILES} ${WWISE_COMMON} ${WWISE_POSIX})

if (${CMAKE_BUILD_TYPE} STREQUAL "Profile")
    target_link_libraries(${LIB_NAME} -lCommunicationCentral)
endif()

target_link_libraries(${LIB_NAME} -lAkMemoryMgr -lAkMusicEngine -lAkSoundEngine -lAkStreamMgr -lAkVorbisDecoder -lAkAudioInputSource -lAkSilenceSource -lAkSineSource -lAkSynthOne -lAkToneSource -AkCompressor -lAkMotion -lAkRecorder -lAudioInput -lSilenceGenerator -lSine -lSynthOne -lToneGen -lAkCompressorFX -lAkConvolutionReverbFX -lAkDelayFX -lAkExpanderFX -lAkFlangerFX -lAkGainFX -lAkGuitarDistortionFX -lAkHarmonizerFX -lAkMatrixReverbFX -lAkMeterFX -lAkParametricEQFX -lAkPeakLimiterFX -lAkPitchShifterFX -lAkRecorderFX -lAkRoomVerbFX -lAkStereoDelayFX -lAkTimeStretchFX -lAkTremoloFX -lAkSoundSeedImpactFX -lAkSoundSeedWind -lAkSoundSeedWoosh -lSDL2 -ldl -lpthread)


