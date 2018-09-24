# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

add_definitions(
             -DHAVE_STDLIB_H
             -DSTDC_HEADERS
             -DHAVE_UNISTD_H
             -D HAVE_STRING_H
             -DHAVE_MATH_H
             -DHAVE_LIMITS_H
             -DHAVE_SYS_TYPES_H
             -DSIZEOF_SHORT=sizeof\(short\)
             -DSIZEOF_LONG=sizeof\(long\)
             -DSPRO
             )

include_directories(
             src/main/cpp/alize-core/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/include/Eigen
             src/main/cpp/LIA_RAL/include/lapacke
             src/main/cpp/LIA_RAL/LIA_SpkTools/include

             src/main/cpp/LIA_RAL/LIA_SpkDet/ComputeJFAStats/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/ComputeNorm/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/ComputeTest/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/CovIntra/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/CovIntra/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/EigenChannel/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/EigenVoice/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/EnergyDetector/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/EstimateDMatrix/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/IvExtractor/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/IvNorm/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/IvTest/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/NormFeat/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/NormFeatWindowMode/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/PLDA/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/RemoteSpkDet/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/RemoteSpkDet/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/ShiftedDeltaFeat/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/SimpleSpkDetSystem/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/SpkAdapt/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/TotalVariability/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/TrainTarget/include
             src/main/cpp/LIA_RAL/LIA_SpkDet/TrainWorld/include
             src/main/cpp/LIA_RAL/LIA_SpkSeg/AcousticSegmentation/include
             src/main/cpp/LIA_RAL/LIA_SpkSeg/ReSegmentation/include
             src/main/cpp/LIA_RAL/LIA_SpkSeg/Segmentation/include
             src/main/cpp/LIA_RAL/LIA_SpkSeg/TurnDetection/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_SpkTools/include
             src/main/cpp/LIA_RAL/LIA_Utils/BNGram/include
             src/main/cpp/LIA_RAL/LIA_Utils/ExtractParams/include
             src/main/cpp/LIA_RAL/LIA_Utils/FusionScore/include
             src/main/cpp/LIA_RAL/LIA_Utils/GmmTokenizer/include
             src/main/cpp/LIA_RAL/LIA_Utils/Hist/include
             src/main/cpp/LIA_RAL/LIA_Utils/LabelFusion/include
             src/main/cpp/LIA_RAL/LIA_Utils/LabelNGram/include
             src/main/cpp/LIA_RAL/LIA_Utils/PolyExp/include
             src/main/cpp/LIA_RAL/LIA_Utils/ReadFeatFile/include
             src/main/cpp/LIA_RAL/LIA_Utils/ReadModel/include
             src/main/cpp/LIA_RAL/LIA_Utils/Scoring/include
             src/main/cpp/LIA_RAL/LIA_Utils/SequenceExtractor/include
             src/main/cpp/LIA_RAL/LIA_Utils/Svm/include
             src/main/cpp/LIA_RAL/LIA_Utils/Svm/include

             src/main/cpp/spro
              )

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             alize-native

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/AlizeSpkRec_AlizeException.cpp
             src/main/cpp/AlizeSpkRec_SimpleSpkDetSystem.cpp

             # ALIZE Core
             src/main/cpp/alize-core/src/alizeString.cpp
             src/main/cpp/alize-core/src/AudioFileReader.cpp
             src/main/cpp/alize-core/src/AudioFrame.cpp
             src/main/cpp/alize-core/src/AudioInputStream.cpp
             src/main/cpp/alize-core/src/AutoDestructor.cpp
             src/main/cpp/alize-core/src/BoolMatrix.cpp
             src/main/cpp/alize-core/src/CmdLine.cpp
             src/main/cpp/alize-core/src/Config.cpp
             src/main/cpp/alize-core/src/ConfigChecker.cpp
             src/main/cpp/alize-core/src/ConfigFileReaderAbstract.cpp
             src/main/cpp/alize-core/src/ConfigFileReaderRaw.cpp
             src/main/cpp/alize-core/src/ConfigFileReaderXml.cpp
             src/main/cpp/alize-core/src/ConfigFileWriter.cpp
             src/main/cpp/alize-core/src/Distrib.cpp
             src/main/cpp/alize-core/src/DistribGD.cpp
             src/main/cpp/alize-core/src/DistribGF.cpp
             src/main/cpp/alize-core/src/DistribRefVector.cpp
             src/main/cpp/alize-core/src/DoubleSquareMatrix.cpp
             src/main/cpp/alize-core/src/Exception.cpp
             src/main/cpp/alize-core/src/Feature.cpp
             src/main/cpp/alize-core/src/FeatureFileList.cpp
             src/main/cpp/alize-core/src/FeatureFileReader.cpp
             src/main/cpp/alize-core/src/FeatureFileReaderAbstract.cpp
             src/main/cpp/alize-core/src/FeatureFileReaderHTK.cpp
             src/main/cpp/alize-core/src/FeatureFileReaderRaw.cpp
             src/main/cpp/alize-core/src/FeatureFileReaderSingle.cpp
             src/main/cpp/alize-core/src/FeatureFileReaderSPro3.cpp
             src/main/cpp/alize-core/src/FeatureFileReaderSPro4.cpp
             src/main/cpp/alize-core/src/FeatureFileWriter.cpp
             src/main/cpp/alize-core/src/FeatureFlags.cpp
             src/main/cpp/alize-core/src/FeatureInputStream.cpp
             src/main/cpp/alize-core/src/FeatureInputStreamModifier.cpp
             src/main/cpp/alize-core/src/FeatureMultipleFileReader.cpp
             src/main/cpp/alize-core/src/FeatureServer.cpp
             src/main/cpp/alize-core/src/FileReader.cpp
             src/main/cpp/alize-core/src/FileWriter.cpp
             src/main/cpp/alize-core/src/FrameAcc.cpp
             src/main/cpp/alize-core/src/FrameAccGD.cpp
             src/main/cpp/alize-core/src/FrameAccGF.cpp
             src/main/cpp/alize-core/src/Histo.cpp
             src/main/cpp/alize-core/src/Label.cpp
             src/main/cpp/alize-core/src/LabelFileReader.cpp
             src/main/cpp/alize-core/src/LabelServer.cpp
             src/main/cpp/alize-core/src/LabelSet.cpp
             src/main/cpp/alize-core/src/LKVector.cpp
             src/main/cpp/alize-core/src/Matrix.cpp
             src/main/cpp/alize-core/src/Mixture.cpp
             src/main/cpp/alize-core/src/MixtureDict.cpp
             src/main/cpp/alize-core/src/MixtureFileReader.cpp
             src/main/cpp/alize-core/src/MixtureFileReaderAbstract.cpp
             src/main/cpp/alize-core/src/MixtureFileReaderAmiral.cpp
             src/main/cpp/alize-core/src/MixtureFileReaderRaw.cpp
             src/main/cpp/alize-core/src/MixtureFileReaderXml.cpp
             src/main/cpp/alize-core/src/MixtureFileWriter.cpp
             src/main/cpp/alize-core/src/MixtureGD.cpp
             src/main/cpp/alize-core/src/MixtureGDStat.cpp
             src/main/cpp/alize-core/src/MixtureGF.cpp
             src/main/cpp/alize-core/src/MixtureGFStat.cpp
             src/main/cpp/alize-core/src/MixtureServer.cpp
             src/main/cpp/alize-core/src/MixtureServerFileReader.cpp
             src/main/cpp/alize-core/src/MixtureServerFileReaderAbstract.cpp
             src/main/cpp/alize-core/src/MixtureServerFileReaderRaw.cpp
             src/main/cpp/alize-core/src/MixtureServerFileReaderXml.cpp
             src/main/cpp/alize-core/src/MixtureServerFileWriter.cpp
             src/main/cpp/alize-core/src/MixtureStat.cpp
             src/main/cpp/alize-core/src/Object.cpp
             src/main/cpp/alize-core/src/Seg.cpp
             src/main/cpp/alize-core/src/SegAbstract.cpp
             src/main/cpp/alize-core/src/SegCluster.cpp
             src/main/cpp/alize-core/src/SegServer.cpp
             src/main/cpp/alize-core/src/SegServerFileReaderAbstract.cpp
             src/main/cpp/alize-core/src/SegServerFileReaderRaw.cpp
             src/main/cpp/alize-core/src/SegServerFileWriter.cpp
             src/main/cpp/alize-core/src/StatServer.cpp
             src/main/cpp/alize-core/src/ULongVector.cpp
             src/main/cpp/alize-core/src/ViterbiAccum.cpp
             src/main/cpp/alize-core/src/XLine.cpp
             src/main/cpp/alize-core/src/XList.cpp
             src/main/cpp/alize-core/src/XListFileReader.cpp
             src/main/cpp/alize-core/src/XmlParser.cpp

             # LIA_SpkTools
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/AccumulateJFAStat.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/AccumulateStat.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/AccumulateTVStat.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/ClusteringCriterion.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/FactorAnalysis.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/FileInfo.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/GeneralTools.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/Hmm.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/IOFormat.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/liatools.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/PldaTools.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/ScoreWarp.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/SegTools.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/SuperVectors.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/Tools.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/TopGauss.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/TrainTools.cpp
             src/main/cpp/LIA_RAL/LIA_SpkTools/src/UnsupervisedTools.cpp

             # LIA_SpkDet
             src/main/cpp/LIA_RAL/LIA_SpkDet/ComputeJFAStats/src/ComputeJFAStats.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/ComputeNorm/src/ComputeNorm.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/ComputeTest/src/ComputeTest.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/CovIntra/src/CovIntra.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/CovIntra/src/SVDLIBC/las2.c
             src/main/cpp/LIA_RAL/LIA_SpkDet/CovIntra/src/SVDLIBC/main.c
             src/main/cpp/LIA_RAL/LIA_SpkDet/CovIntra/src/SVDLIBC/svdlib.c
             src/main/cpp/LIA_RAL/LIA_SpkDet/CovIntra/src/SVDLIBC/svdutil.c
             src/main/cpp/LIA_RAL/LIA_SpkDet/EigenVoice/src/EigenVoice.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/EnergyDetector/src/EnergyDetector.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/EstimateDMatrix/src/EstimateDMatrix.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/IvExtractor/src/IvExtractor.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/IvNorm/src/IvNorm.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/IvTest/src/IvTest.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/NormFeat/src/NormFeat.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/NormFeatWindowMode/src/NormFeatWindowMode.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/PLDA/src/PLDA.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/RemoteSpkDet/src/SpkDetServer.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/SimpleSpkDetSystem/src/SimpleSpkDetSystem.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/SpkAdapt/src/SpkAdapt.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/TotalVariability/src/TotalVariability.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/TrainTarget/src/TrainTarget.cpp
             src/main/cpp/LIA_RAL/LIA_SpkDet/TrainWorld/src/TrainWorld.cpp

             # LIA_SpkSeg
             src/main/cpp/LIA_RAL/LIA_SpkSeg/AcousticSegmentation/src/AcousticSegmentation.cpp
             src/main/cpp/LIA_RAL/LIA_SpkSeg/ReSegmentation/src/ReSegmentation.cpp
             src/main/cpp/LIA_RAL/LIA_SpkSeg/Segmentation/src/Segmentation.cpp
             src/main/cpp/LIA_RAL/LIA_SpkSeg/TurnDetection/src/TurnDetection.cpp

             # LIA_Utils
             src/main/cpp/LIA_RAL/LIA_Utils/BNGram/src/BNGram.cpp
             src/main/cpp/LIA_RAL/LIA_Utils/ExtractParams/src/ExtractParams.cpp
             src/main/cpp/LIA_RAL/LIA_Utils/FusionScore/src/FusionScore.cpp
             src/main/cpp/LIA_RAL/LIA_Utils/GmmTokenizer/src/GmmTokenizer.cpp
             src/main/cpp/LIA_RAL/LIA_Utils/Hist/src/Hist.cpp
             src/main/cpp/LIA_RAL/LIA_Utils/LabelFusion/src/LabelFusion.cpp
             src/main/cpp/LIA_RAL/LIA_Utils/LabelNGram/src/LabelNGram.cpp
             src/main/cpp/LIA_RAL/LIA_Utils/PolyExp/src/PolyExpand.cpp
             src/main/cpp/LIA_RAL/LIA_Utils/ReadFeatFile/src/ReadFeatFile.cpp
             src/main/cpp/LIA_RAL/LIA_Utils/ReadModel/src/ReadModel.cpp
             src/main/cpp/LIA_RAL/LIA_Utils/Scoring/src/Scoring.cpp
             src/main/cpp/LIA_RAL/LIA_Utils/SequenceExtractor/src/SequenceExtractor.cpp
             src/main/cpp/LIA_RAL/LIA_Utils/Svm/src/libsvm.cpp
             src/main/cpp/LIA_RAL/LIA_Utils/Svm/src/Svm.cpp

             # SPro 5
             src/main/cpp/spro/sig.c
             src/main/cpp/spro/spf.c
             src/main/cpp/spro/header.c
             src/main/cpp/spro/misc.c
             src/main/cpp/spro/lpc.c
             src/main/cpp/spro/convert.c
             src/main/cpp/spro/fft.c
             )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       alize-native

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )