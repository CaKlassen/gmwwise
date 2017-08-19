cmake_minimum_required(VERSION 3.7)
project(GMWwise)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        ${CMAKE_CURRENT_DIR}../../../../Wwise/include
        ${CMAKE_CURRENT_DIR}../../../../Wwise/samples/SoundEngine/Common
        ${CMAKE_CURRENT_DIR}../../../../Wwise/samples/SoundEngine/POSIX
        ${CMAKE_CURRENT_DIR}../../../../)

set(SOURCE_FILES
        ../Shared/GMWConfig.cpp
        ../Shared/GMWConfig.h
        ../Shared/GMWEngine.cpp
        ../Shared/GMWEngine.h
        ../Shared/GMWBank.cpp
        ../Shared/GMWBank.h
        ../Shared/GMWGameObject.cpp
        ../Shared/GMWGameObject.h
        ../Shared/GMWListener.cpp
        ../Shared/GMWListener.h
        ../Shared/GMWStringUtil.cpp
        ../Shared/GMWStringUtil.h)

# Define build configuration pre-processor macros
set(CMAKE_CXX_FLAGS "-m32 ${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "-m32 ${CMAKE_C_FLAGS}")

if(${CMAKE_BUILD_TYPE} STREQUAL "Profile")
    add_definitions(-DDEBUG=1 -DAK_OPTIMIZED)
    set(LIB_NAME "GMWwise_profile")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(LIB_NAME "GMWwise")
endif()

link_directories("../../../../Wwise/Linux_x32/${CMAKE_BUILD_TYPE}/lib")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lAkHarmonizerFX -lAkMeterFX -lAkStereoDelayFX -lAkConvolutionReverbFX -lAkPitchShifterFX -lAkRoomVerbFX -lAkTremoloFX -lAkGuitarDistortionFX -lAkSineSource -lAkCompressorFX -lAkExpanderFX -lAkMatrixReverbFX -lAkDelayFX -lAkGainFX -lAkParametricEQFX -lAkRoomVerbFX -lAkPeakLimiterFX -lAkSynthOne -lAkSilenceSource -lAkAudioInputSource -lAkVorbisDecoder -lAkStreamMgr -lAkSoundEngine -lAkMusicEngine -lAkMemoryMgr -lAkToneSource -lAkFlangerFX -lMcDSPFutzBoxFX -lMcDSPLimiterFX -lAkSoundSeedWind -lAkSoundSeedWoosh -lAkSoundSeedImpactFX -lAkRecorderFX -lCrankcaseAudioREVModelPlayerFX -lAkTimeStretchFX")

if(${CMAKE_BUILD_TYPE} STREQUAL "Profile")
    set(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} -lCommunicationCentral")
endif()

add_library(${LIB_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${LIB_NAME} AkHarmonizerFX AkMeterFX AkStereoDelayFX AkConvolutionReverbFX AkPitchShifterFX AkRoomVerbFX AkTremoloFX AkGuitarDistortionFX AkSineSource AkCompressorFX AkExpanderFX AkMatrixReverbFX AkDelayFX AkGainFX AkParametricEQFX AkRoomVerbFX AkPeakLimiterFX AkSynthOne AkSilenceSource AkAudioInputSource AkVorbisDecoder AkStreamMgr AkSoundEngine AkMusicEngine AkMemoryMgr AkToneSource AkFlangerFX McDSPFutzBoxFX McDSPLimiterFX AkSoundSeedWind AkSoundSeedWoosh AkSoundSeedImpactFX AkRecorderFX CrankcaseAudioREVModelPlayerFX AkTimeStretchFX)
