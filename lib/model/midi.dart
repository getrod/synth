import 'dart:async';
import 'dart:math';
import 'package:flutter/foundation.dart';
import 'midiPlatform.dart';

/// Add Channel attribute to MidiEvent
class MidiEvent {
  MidiEvent({
    this.isOn,
    this.note,
    this.velocity,
  })  : assert(isOn != null),
        assert(note != null),
        assert(velocity != null);

  MidiEvent.off({this.note})
      : assert(note != null),
        isOn = false,
        velocity = 0;

  MidiEvent.on({
    this.note,
    this.velocity,
  })  : assert(note != null),
        assert(velocity != null),
        isOn = true;

  final bool isOn;
  final int note;
  final int velocity;
  static const double c0 = 16.35;

  double get frequency => c0 * pow(2, ((note * 100) / 1200));

  toString() {
    return 'MidiEvent{$isOn, $note, $velocity}';
  }
}

class MidiTrackEvent {
  MidiEvent midiEvent;
  double deltaTime;

  MidiTrackEvent({
    this.midiEvent,
    this.deltaTime,
  }) : assert(deltaTime != null);

  toString() {
    return 'MidiTrackEvent{$deltaTime, $midiEvent}';
  }
}

class MidiTrack {
  List<MidiTrackEvent> _events = [];
  List<MidiTrackEvent> get events => _events;

  void sortEvents() {
    _events.sort((a, b) => a.deltaTime.compareTo(b.deltaTime));
  }

  toString() {
    String s = '';
    for (final e in _events) {
      s += e.toString() + '\n';
    }
    return s;
  }
}

///Add callback attribute to this class to call playnote funciton
class TrackPlayer {
  TrackPlayer({
    this.maxBpm = 300,
    this.minBpm = 20,
    this.minDeltaTime = 1 / 24,
    @required this.bpm,
    @required this.track,
  })  : assert(bpm != null),
        assert(track != null),
        secondsPerBeat = 60 / bpm,
        period = minDeltaTime * (60 / bpm) {
    timer = createTimer();
  }

  final double maxBpm;
  final double minBpm;
  final double minDeltaTime;
  double bpm;
  double secondsPerBeat;
  double period;
  int counter = 0;
  bool isPlaying = false;
  MidiTrack track;
  Timer timer;
  Stopwatch stopWatch = Stopwatch();

  Timer createTimer() {
    return Timer.periodic(Duration(milliseconds: (period * 1000).toInt()), timerCallback);
  }

  void timerCallback(Timer t) {
    if (!isPlaying) {return;}
    
    if (counter < track.events.length) {
      if (track.events.elementAt(counter).deltaTime * secondsPerBeat <= stopWatch.elapsed.inMilliseconds / 1000) {
        //Callback to platform
        //print(track.events.elementAt(counter).toString() + ' ' + (stopWatch.elapsed.inMilliseconds / 1000).toString());
        MidiPlatform.sendMidiEvent(track.events.elementAt(counter).midiEvent);
        counter++;
      }
    } else {
      //print('End of track');
      //stop();
      loop();
    }
  }

  void play() {
    if (isPlaying) {return;}
    //print('play');
    track.sortEvents();
    isPlaying = true;
    stopWatch.start();
  }

  void pause() {
    isPlaying = false;
    stopWatch.stop();
  }

  void stop() {
    isPlaying = false;
    stopWatch.stop();
    stopWatch.reset();
    counter = 0;
  }

  void loop() {
    stop();
    play();
  }
}


