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


### What is needed to build ALIZÉ for Android?

You need to get the source for `alize-core` and `LIA_RAL` from their respective repositories, and put the two source folders at this path:
`{project_root}/alize/src/main/cpp/`

In order to parameterize the audio signal, this package uses SPro:
<https://gforge.inria.fr/projects/spro/>

Download the source from the SPro website and put the folder at the same path as the other two (the name for the folder is expected to be `spro`, with no version number).


### How to compile

Once all three source folders (`alize-core`, `LIA_RAL`, `spro`) are in place, open the project with Android Studio.
In the `Build` menu, select `Build APK`. It will generate an Android archive for ALIZÉ, which you can then import as a module in your application projects.


### How to use it

#### Import the library

In Android Studio, import the AAR archive into your application project as a new module (`File` ▸ `New` ▸ `New Module…`, then `Import .JAR/.AAR Package`). Remember to update the app module's `build.gradle` file to include the library in the dependencies.

The procedure is detailed on this webpage: <https://developer.android.com/studio/projects/android-library.html>

The Java classes providing access to ALIZÉ are then available in the `AlizeSpkRec` package:
```java
import AlizeSpkRec.*;
```

#### Create an instance of a speaker recognition system

In order to create a new speaker recognition system, two things are needed:

- a configuration file
- a path to a directory where the system can store files (speakers models + temporary files)

The configuration can be provided by passing the constructor either a file name, or an input stream.
The latter is particularly useful in the common case where the configuration file is packaged as an application asset, as illustrated below.

```java
InputStream configAsset = getApplicationContext().getAssets().open("AlizeDefault.cfg");
SimpleSpkDetSystem alizeSystem = new SimpleSpkDetSystem(configAsset, getApplicationContext().getFilesDir().getPath());
configAsset.close();
```

We then load the background model, also from the application assets.

```java
InputStream backgroundModelAsset = getApplicationContext().getAssets().open("gmm/world.gmm");
alizeSystem.loadBackgroundModel(backgroundModelAsset);
backgroundModelAsset.close();
```

#### Check system status
```java
System.out.println("System status:");
System.out.println("  # of features: " + alizeSystem.featureCount());   // at this point, 0
System.out.println("  # of models: " + alizeSystem.speakerCount());     // at this point, 0
System.out.println("  UBM is loaded: " + alizeSystem.isUBMLoaded());    // true
```

#### Train a speaker model
```java
// Record audio in the format specified in the configuration file and return it as an array of bytes
byte[] audio = …

// Send audio to the system
alizeSystem.addAudio(audio);

// Train a model with the audio
alizeSystem.createSpeakerModel("Somebody");
```

After this, `alizeSystem.speakerCount()` returns 1.
`alizeSystem.featureCount()` > 0 and corresponds to the number of feature vectors extracted from the audio signal.


#### Reset input before sending another signal
```java
alizeSystem.resetAudio();
alizeSystem.resetFeatures();
```

#### Perform speaker verification
```java
// Record some more audio
audio = …

// Send the new audio to the system
alizeSystem.addAudio(audio);

// Perform speaker verification against the model we created earlier
SpkRecResult verificationResult = alizeSystem.verifySpeaker("Somebody");
```

`verificationResult.match` is a boolean indicating the resulting decision: if `true`, the signal matches the speaker model.
`verificationResult.score` gives the score on which the decision is based.


#### Load a pre-trained speaker model packaged with the application
```java
InputStream modelAsset = getApplicationContext().getAssets().open("gmm/somebody_else.gmm");
alizeSystem.loadSpeakerModel("Somebody else", modelAsset);
modelAsset.close();
```

At this point, `alizeSystem.speakerCount() == 2`.


#### Perform speaker identification
With two speaker models, we can try speaker identification.
We will use the same audio signal as previously.
Since we have not unloaded it yet (through `alizeSystem.resetAudio()` and `alizeSystem.resetFeatures()`), there is no need to resend it.

```java
SpkRecResult identificationResult = alizeSystem.identifySpeaker();
```

`identificationResult.match` is a boolean indicating the resulting decision: if `true`, the signal matches the speaker model.
`identificationResult.speakerId`
`identificationResult.score` gives the score on which the decision is based.


#### Exceptions

All the methods of class SimpleSpkDetSystem throw exceptions of type AlizeException in case of a problem encountered by the underlying C++ library.
