import 'package:flutter/material.dart';
import "package:flutter/services.dart";
import 'keyboard.dart';
void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  Widget build(BuildContext context) {
    return MaterialApp(
      title: "Synth Test",
      home: Scaffold(
        body: Center(
          child: KeyboardScreen(),
        ),
      ),
    );
  }
}

class KeyboardScreen extends StatefulWidget {
  _KeyboardScreenState createState() => _KeyboardScreenState();
}

class _KeyboardScreenState extends State<KeyboardScreen> {
  void initState() {
    super.initState();
    SystemChrome.setPreferredOrientations([
      DeviceOrientation.landscapeRight,
      DeviceOrientation.landscapeLeft,
    ]);
  }

  void dispose() {
    SystemChrome.setPreferredOrientations([
      DeviceOrientation.landscapeRight,
      DeviceOrientation.landscapeLeft,
      DeviceOrientation.portraitUp,
      DeviceOrientation.portraitDown
    ]);
    super.dispose();
  }

  Widget build(BuildContext context) {
    return Keyboard();
  }
}
