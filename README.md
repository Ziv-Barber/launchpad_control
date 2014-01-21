# launchpad_control

Simple example how to control Novation Launchpad to debug application in Visual Studio.

## Sample video

Click [here](<http://www.youtube.com/watch?v=LOyNUGS4RC8>)

## Tools needed

- Visual Studio 2013. The C++ code itself can be compiled also in Visual Studio 2010 but you need to convert yourself the project files.
- wxWidgets pre-compiled to either 32 bits or 64 bits - download [here](<http://www.wxwidgets.org/>)
- rtmidi library pre-compiled to either 32 bits or 64 bits - download [here](<http://www.music.mcgill.ca/~gary/rtmidi/>)

## Preparation

I'm sorry but this source package is not ready to compile out of the box and you need to do the following operations:

- Download wxWidgets and compile it to either 32 bits or 64 bits (or both).
- Download rtmidi and compile it to either 32 bits or 64 bits (or both).
- Copy LaunchPadGenControl.example to LaunchPadGenControl\LaunchPadGenControl.vcxproj.user
- Edit LaunchPadGenControl\LaunchPadGenControl.vcxproj.user to fix the location of all the includes and libs of both wxwidgets and rtmidi.
- Now you can compile it.

## Mapped Launchpad keys:

- Top control line to F1-F8.
- Right side control line to F5-F12.

## Warnings

- I didn't test the 32 bits configuration but it should work fine.
- While I used wxWidgets 3.0.0, my wx code is compatible with any of the 2.9.x versions.
- I have Launchpad S.
- Please install the Launchpad USB drivers.
- Since that it's a fast hack, then I didn't tests too much for MIDI errors.

