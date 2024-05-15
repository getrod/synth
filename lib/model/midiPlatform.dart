import 'package:flutter/services.dart';
import 'midi.dart';

class MidiPlatform {
  static const MethodChannel _channel = MethodChannel('buuk/synth');

  static startAudioEngine() {
    return _channel.invokeMethod('audioEngineInit');
  }
  
  static sendMidiEvent(MidiEvent event) {
    if (event.isOn) {
      return _channel.invokeMethod('noteOn', {"noteId": event.note, "frequency": event.frequency});
    } else {
      return _channel.invokeMethod('noteOff', {"noteId": event.note});
    }
    
  }
}