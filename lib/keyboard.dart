import 'package:flutter/material.dart';
import "package:flutter/services.dart";
import 'note_button.dart';

//Extra stuff
import 'model/midi.dart';

class Keyboard extends StatefulWidget {
  _KeyboardState createState() => _KeyboardState();
}

class _KeyboardState extends State<Keyboard> {
  final Color whiteKeysColor = Colors.grey;
  final Color blackKeysColor = Colors.black;
  static const platform = const MethodChannel("buuk/synth");

  TrackPlayer player;

  @override
  void initState() {
    
    platform.invokeMethod("audioEngineInit");
    player = TrackPlayer(
      bpm: 120,
      track: MidiTrack()..events
        .addAll([
          MidiTrackEvent(
            deltaTime: 0,
            midiEvent: MidiEvent.on(note: 60, velocity: 0),
          ),
          MidiTrackEvent(
            deltaTime: 1/4,
            midiEvent: MidiEvent.off(note: 60)
          ),
          MidiTrackEvent(
            deltaTime: 1,
            midiEvent: MidiEvent.on(note: 60, velocity: 0),
          ),
          MidiTrackEvent(
            deltaTime: 1 + 1/4,
            midiEvent: MidiEvent.off(note: 60)
          ),
          MidiTrackEvent(
            deltaTime: 2,
            midiEvent: MidiEvent.on(note: 60, velocity: 0),
          ),
          MidiTrackEvent(
            deltaTime: 2 + 1/4,
            midiEvent: MidiEvent.off(note: 60)
          ),
          MidiTrackEvent(
            deltaTime: 3,
            midiEvent: MidiEvent.on(note: 60, velocity: 0),
          ),
          MidiTrackEvent(
            deltaTime: 3 + 1/4,
            midiEvent: MidiEvent.off(note: 60)
          ),
          MidiTrackEvent(
            deltaTime: 4,
            midiEvent: MidiEvent.off(note: 60,),
          ),
        ])
    );
    super.initState();
  }

  @override
  void dispose() {
    player.timer.cancel();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Container(
      alignment: Alignment.center,
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: <Widget>[
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              Expanded(
                child: Container(),
              ),
              Expanded(
                child: NoteButton(
                  onTapDown: () {},
                  onTapUp: () {},
                  onTapCancel: () {},
                  defaultColor: blackKeysColor,
                  frequency: 277.18,  //C#
                ),
              ),
              Expanded(
                child: NoteButton(
                  onTapDown: () {},
                  onTapUp: () {},
                  onTapCancel: (){},
                  defaultColor: blackKeysColor,
                  frequency: 311.13,  //D#
                ),
              ),
              Expanded(
                child: Container(),
              ),
              Expanded(
                child: Container(),
              ),
              Expanded(
                child: NoteButton(
                  onTapDown: () {},
                  onTapUp: () {},
                  onTapCancel: (){},
                  defaultColor: blackKeysColor,
                  frequency: 369.99,  //F#
                ),
              ),
              Expanded(
                child: NoteButton(
                  onTapDown: () {},
                  onTapUp: () {},
                  onTapCancel: (){},
                  defaultColor: blackKeysColor,
                  frequency: 415.30,  //G#
                ),
              ),
              Expanded(
                child: NoteButton(
                  onTapDown: () {},
                  onTapUp: () {},
                  onTapCancel: (){},
                  defaultColor: blackKeysColor,
                  frequency: 466.16,  //A#
                ),
              ),
              Expanded(
                child: Container(),
              ),
            ],
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              Expanded(
                child: NoteButton(
                  onTapDown: () {
                    player.play();
                  },
                  onTapUp: () {},
                  onTapCancel: (){},
                  defaultColor: whiteKeysColor,
                  frequency: 261.63,  //C
                ),
              ),
              Expanded(
                child: NoteButton(
                  onTapDown: () {
                    player.stop();
                  },
                  onTapUp: () {},
                  onTapCancel: (){},
                  defaultColor: whiteKeysColor,
                  frequency: 293.66,  //D
                ),
              ),
              Expanded(
                child: NoteButton(
                  onTapDown: () {},
                  onTapUp: () {},
                  onTapCancel: (){},
                  defaultColor: whiteKeysColor,
                  frequency: 329.63,  //E
                ),
              ),
              Expanded(
                child: NoteButton(
                  onTapDown: () {},
                  onTapUp: () {},
                  onTapCancel: (){},
                  defaultColor: whiteKeysColor,
                  frequency: 349.23,  //F
                ),
              ),
              Expanded(
                child: NoteButton(
                  onTapDown: () {},
                  onTapUp: () {},
                  onTapCancel: (){},
                  defaultColor: whiteKeysColor,
                  frequency: 392.00,  //G
                ),
              ),
              Expanded(
                child: NoteButton(
                  onTapDown: () {},
                  onTapUp: () {},
                  onTapCancel: (){},
                  defaultColor: whiteKeysColor,
                  frequency: 440.00,  //A
                ),
              ),
              Expanded(
                child: NoteButton(
                  onTapDown: () {},
                  onTapUp: () {},
                  onTapCancel: (){},
                  defaultColor: whiteKeysColor,
                  frequency: 493.88,  //B
                ),
              ),
            ],
          )
        ],
      ),
    );
  }
}