<img src="http://alize.univ-avignon.fr/images/alize-logo.png" alt="The ALIZÉ logo" height="198" >

# ALIZÉ for Android

*This package is part of the ALIZÉ project: <http://alize.univ-avignon.fr>*



Welcome to ALIZÉ
----------------

ALIZÉ is a software platform for automatic speaker recognition. It can be used for carrying out research in this field, as well as for incorporating speaker recognition into applications.

<http://alize.univ-avignon.fr>


ALIZÉ for Android
-----------------

This repository hosts material to allow people to compile and use ALIZÉ (`alize-core` and `LIA_RAL`) on the Android platform:
    - a project for Android Studio to help compile ALIZÉ into an Android library (in AAR format) for inclusion in applications
    - a JNI layer to facilitate access to ALIZÉ (which is developed in C++) from Java sources.

The repository does not contain the sources of ALIZÉ itself (see below for how to download and install them).

The JNI layer does not, at this time, offer complete access to all of the classes in ALIZÉ.
For now, it focuses only on offering access to high-level APIs which allow to run a speaker detection system (for speaker verification/identification) on the Android platform. It uses the class SimpleSpkDetSystem and provides the same API as the C++ version of this class.

Through this API, a user can feed the system audio data and use it to train speaker models, and run speaker verification and identification tasks.
It is the responsibility of the host application to perform audio capture from the microphone or any other device — the ALIZÉ library does no provide this function.


#### What is needed to build ALIZÉ for Android?

You need to get the source for `alize-core` and `LIA_RAL` from their respective repositories, and put the two source folders at this path:
`{project_root}/alize/src/main/cpp/`

In order to parameterize the audio signal, this package uses SPro:
<https://gforge.inria.fr/projects/spro/>

Download the source from the SPro website and put the folder at the same path as the other two (the name for the folder is expected to be `spro`, with no version number).


#### How to compile

Once all three source folders (`alize-core`, `LIA_RAL`, `spro`) are in place, open the project with Android Studio.
In the `Build` menu, select `Build APK`. It will generate an Android archive for ALIZÉ, which you can then import as a module in your application projects.
