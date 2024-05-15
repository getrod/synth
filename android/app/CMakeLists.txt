cmake_minimum_required(VERSION 3.4.1)

set (
    APP_SOURCES
    src/main/cpp/jniBridge.cpp
    src/main/cpp/buukSynth/Envelope.cpp
    src/main/cpp/buukSynth/Oscillator.cpp
    src/main/cpp/buukSynth/Synth.cpp
    src/main/cpp/buukSynth/Waveform.cpp
    src/main/cpp/buukSynth/WaveformUtils.h
    src/main/cpp/AudioEngine.cpp
)

add_library (native-lib SHARED ${APP_SOURCES})

# Build the Oboe library
set (OBOE_DIR C:/Users/Kevin/oboe)
add_subdirectory (${OBOE_DIR} ./oboe)

# Make the Oboe public headers available to our app
include_directories (${OBOE_DIR}/include)

# Specify the libraries which our native library is dependent on, including Oboe
target_link_libraries (native-lib android log oboe)