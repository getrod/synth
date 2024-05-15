package com.example.synth

import androidx.annotation.NonNull;
import io.flutter.embedding.android.FlutterActivity
import io.flutter.embedding.engine.FlutterEngine
import io.flutter.plugins.GeneratedPluginRegistrant

import io.flutter.plugin.common.MethodChannel

class MainActivity: FlutterActivity() {
    private val CHANNEL = "buuk/synth"
    private var enginePtr : Long = 0
    private val NOENGINE : Long = 0
    private val TAG = "SynthEngine"
    private var mNoteId : Int? = 0
    private var mFrequency : Double? = 0.0

    override fun configureFlutterEngine(@NonNull flutterEngine: FlutterEngine) {
        GeneratedPluginRegistrant.registerWith(flutterEngine);

        MethodChannel(flutterEngine.dartExecutor.binaryMessenger, CHANNEL).setMethodCallHandler {
            call, result ->

            if (call.method == "audioEngineInit") {
                createEngine()
            } else if (call.method == "noteOn") {
                mNoteId = call.argument<Int>("noteId")
                mFrequency = call.argument<Double>("frequency")
                playNote(mNoteId, mFrequency)
            } else if (call.method == "noteOff") {
                mNoteId = call.argument<Int>("noteId")
                stopNote(mNoteId)
            }
        }
    }

    external fun noteOn(engine: Long, noteId: Int, frequency: Double)
    external fun noteOff(engine: Long, noteId: Int)
    external fun audioEngineInit() : Long

    fun engineExists() : Boolean {
        return enginePtr != NOENGINE
    }

    fun createEngine() {
        enginePtr = audioEngineInit()
    }

    fun playNote(noteId: Int?, frequency: Double?) {
        if(engineExists()) {
            noteOn(enginePtr, noteId as Int, frequency as Double)
        }
    }

    fun stopNote(noteId: Int?) {
        if(engineExists()) {
            noteOff(enginePtr, noteId as Int)
        }
    }

    // Load Native Library
    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }
}
