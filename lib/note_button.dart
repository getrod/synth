import 'package:flutter/foundation.dart';
import "package:flutter/services.dart";
import 'package:flutter/material.dart';


class NoteButton extends StatefulWidget {

  NoteButton({
    @required this.onTapDown,
    @required this.onTapUp,
    @required this.onTapCancel,
    @required this.defaultColor,
    @required this.frequency,
  });

  final Function onTapDown;
  final Function onTapUp;
  final Function onTapCancel;

  final Color defaultColor;
  final Color highlightColor = Colors.amber[200];
  final double frequency;

  static const platform = const MethodChannel("buuk/synth");

  _NoteButtonState createState() => _NoteButtonState();
}


class _NoteButtonState extends State<NoteButton> {

  Color color;

  void initState() {
    super.initState();
    color = widget.defaultColor;
  }

  Widget build(BuildContext context) {
    return ConstrainedBox(
      constraints: BoxConstraints(
        maxHeight: 150,
        maxWidth: 100,
      ),
      child: GestureDetector(
        onTapDown: (details) {
          widget.onTapDown();
          NoteButton.platform.invokeMethod("noteOn", {"noteId": widget.hashCode, "frequency": widget.frequency});
          setState(() {
            color = widget.highlightColor;
          });
        },
        onTapUp: (details) {
          widget.onTapUp();
          NoteButton.platform.invokeMethod("noteOff", {"noteId": widget.hashCode});
          setState(() {
            color = widget.defaultColor;
          });
        },
        onTapCancel: () {
          widget.onTapCancel();
          NoteButton.platform.invokeMethod("noteOff", {"noteId": widget.hashCode});
          setState(() {
            color = widget.defaultColor;
          });
        },
        child: Container(
          margin: EdgeInsets.all(5),
          decoration: BoxDecoration(
            color: color,
            borderRadius: BorderRadius.circular(8.0),
          ),
        ),
      )
    );
  }
}