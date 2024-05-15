#include <jni.h>
#include <oboe/Oboe.h>
#include "AudioEngine.h"

extern "C" {
JNIEXPORT jlong JNICALL Java_com_example_synth_MainActivity_audioEngineInit
        (JNIEnv *env, jobject obj) {

    auto *engine = new(std::nothrow) AudioEngine();
    return reinterpret_cast<jlong>(engine);
}

JNIEXPORT void JNICALL Java_com_example_synth_MainActivity_noteOn
        (JNIEnv *env, jobject obj, jlong enginePtr, jint note_id, jdouble frequency) {

    auto *engine = reinterpret_cast<AudioEngine *> (enginePtr);
    engine->synth->noteOn((int)note_id, (float)frequency);
}

JNIEXPORT void JNICALL Java_com_example_synth_MainActivity_noteOff
        (JNIEnv *env, jobject obj, jlong enginePtr, jint note_id) {

    auto *engine = reinterpret_cast<AudioEngine *> (enginePtr);
    engine->synth->noteOff((int)note_id);
}

}