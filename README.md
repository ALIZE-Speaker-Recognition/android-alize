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

In order to extract features from the audio signal, ALIZÉ relies on the free speech signal processing toolkit SPro, developed by Guillaume Gravier at IRISA:
<https://gforge.inria.fr/projects/spro/>

You need to download the source code package for SPro (please read the warning below), uncompress/unarchive it, and put the resulting folder at the same path as the other two (`{project_root}/alize/src/main/cpp/`). The name for the folder is expected to be `spro`, with no version number. There is no need to compile SPro using the `configure` script and makefile provided in the package; only access to the source code is required.

⚠️**Warning:** Note that only the revisions 155 and up of SPro are fully compatible with 64-bit CPUs and ALIZÉ. However, at the time of this writing, these versions of SPro are only available through Subversion, and the direct download link given on the website above points to an older revision of SPro 5 which includes a bug leading to corrupted feature files when compiled for 64 bit systems.
If you want to be sure to get the right version of SPro for use with ALIZÉ, you can download it from ALIZÉ's website: <http://alize.univ-avignon.fr/spro-5.0-157.tar.gz>.


### How to compile

Once all three source folders (`alize-core`, `LIA_RAL`, `spro`) are in place, open the project with Android Studio.
When you build the project, it will generate an Android archive (`.aar`) for ALIZÉ, which you can then import as a module in your application projects.


### How to use ALIZÉ in your application

#### Import the library

In Android Studio, import the AAR archive into your application project as a new module (`File` ▸ `New` ▸ `New Module…`, then `Import .JAR/.AAR Package`). Remember to update the app module's `build.gradle` file to include the library in the dependencies.

The procedure is detailed on this webpage: <https://developer.android.com/studio/projects/android-library.html>

The Java classes providing access to ALIZÉ are then available in the `AlizeSpkRec` package:
```java
import AlizeSpkRec.*;
```

#### Audio input

This library does not handle audio recording. Audio is passed to the speaker recognition system using the various `addAudio` methods.

The frequency of the audio signal must be specified in the configuration file, using the parameter `SPRO_sampleRate`.
The default format for the audio samples is **16-bit, signed integer linear PCM**.

The parameter `SPRO_format` may be used in the configuration file in order to specify a different format (refer to `spro.h` for the list of formats supported by SPro). However, it is unlikely to be useful in the context of ALIZÉ for Android.
If a different sample/file format is specified this way, it will be used to process audio data sent to the system using the methods `addAudio(String filename)`, `addAudio(InputStream audioDataStream)` and `addAudio(byte[] audioData)`.
But the method `addAudio(short[] linearPCMSamples)`, as its signature and parameter name imply, always expects 16-bit, signed integer linear PCM, ignoring the setting for `SPRO_format`.


#### Create an instance of a speaker recognition system

In order to create a new speaker recognition system, two things are needed:

- a configuration file
- a path to a directory where the system can store files (speakers models + temporary files)

The configuration can be provided by passing the constructor either a file name, or an input stream.
The latter is particularly useful in the common case where the configuration file is packaged as an application asset, as illustrated below.

```java
InputStream configAsset = getApplicationContext().getAssets().open("MyConfig.cfg");
SimpleSpkDetSystem alizeSystem = new SimpleSpkDetSystem(configAsset, getApplicationContext().getFilesDir().getPath());
configAsset.close();
```

We then load the background model (aka "world model", aka "UBM"), also from the application assets.

```java
InputStream backgroundModelAsset = getApplicationContext().getAssets().open("gmm/world.gmm");
alizeSystem.loadBackgroundModel(backgroundModelAsset);
backgroundModelAsset.close();
```

It is best to fine-tune the configuration to your specific usage of speaker recognition, and to train a background model with data recorded in the conditions matching that usage.
But you may start with the example configuration file provided in this repository (`AlizeExampleConfiguration.cfg`). It matches the configuration used in the GMM/UBM tutorial found on ALIZÉ's web site, which allows you to use the background model generated in the tutorial: run the tutorial, and then copy the file `world.gmm` into your application's assets.
While neither this configuration file nor this background model will be a perfect fit for your application, they provide a good starting point to use during development.


#### Check system status

You may make use of the methods below (particularly `speakerCount`) to display information in your user interface:
```java
System.out.println("System status:");
System.out.println("  # of features: " + alizeSystem.featureCount());   // at this point in our example, 0
System.out.println("  # of models: " + alizeSystem.speakerCount());     // at this point in our example, 0
System.out.println("  UBM is loaded: " + alizeSystem.isUBMLoaded());    // true, since we just loaded it
```

#### Train a speaker model

```java
// Record audio
// The system takes 16-bit, signed integer linear PCM, at the frequency specified in the configuration file.
short[] audio = …

// Send audio to the system
alizeSystem.addAudio(audio);

// Train a model with the audio
alizeSystem.createSpeakerModel("John Doe");
```

After this, `alizeSystem.speakerCount()` returns 1.
`alizeSystem.featureCount()` > 0 and corresponds to the number of feature vectors extracted from the audio signal.

Speaker models reside in RAM and are not automatically written to permanent storage. If you want to keep them between runs of your application, you need to explicitly save them.

```java
// Write a speaker model to disk
alizeSystem.saveSpeakerModel("John Doe", "John Doe");
```


#### Reset input before sending another signal

You may run several operations on the same signal without having to send it to the system every time: perform verification against various speaker models, update one of them, etc.
But once done using this audio signal, it is important to remember to clear the input buffers before starting to work with another, unrelated sound signal.

```java
alizeSystem.resetAudio();
alizeSystem.resetFeatures();
```

`alizeSystem.featureCount()` == 0

#### Perform speaker verification
```java
// Record some more audio
short[] moreAudio = …

// Send the new audio to the system
alizeSystem.addAudio(moreAudio);

// Perform speaker verification against the model we created earlier
SpkRecResult verificationResult = alizeSystem.verifySpeaker("Somebody");
```

`verificationResult.match` is a boolean indicating the resulting decision: if `true`, the signal matches the speaker model.
`verificationResult.score` gives the score on which the decision is based.


#### Load a pre-trained speaker model packaged with the application

For some application, it may make sense to embed some pre-trained speaker models as assets.
You can use the `InputStream`-based version of `loadSpeakerModel` in order to load such models.

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

`identificationResult.match` is a boolean indicating the resulting decision: if `true`, the signal matches one of the speaker models in the database.
`identificationResult.speakerId`, of type String, gives the ID of the best matching speaker.
`identificationResult.score` gives the score obtained for the best matching speaker model.


#### Exceptions

All the methods of class SimpleSpkDetSystem throw exceptions of type AlizeException in case of a problem encountered by the underlying C++ library.
