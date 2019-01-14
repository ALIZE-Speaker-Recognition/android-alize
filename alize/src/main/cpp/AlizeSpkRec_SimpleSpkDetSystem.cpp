#include <string>
#include <vector>
#include "AlizeSpkRec_SimpleSpkDetSystem.h"
#include "SimpleSpkDetSystem.h"
#include "AlizeSpkRec_AlizeException.h"


using namespace alize;


jfieldID getNativeSystemPtrFieldId(JNIEnv * env, jobject obj)
{
    jfieldID ptrFieldId;

    jclass c = env->GetObjectClass(obj);
    ptrFieldId = env->GetFieldID(c, "nativeSystemPtr", "J");
    env->DeleteLocalRef(c);

    return ptrFieldId;
}

SimpleSpkDetSystem* nativeSystem(JNIEnv * env, jobject obj)
{
    return (SimpleSpkDetSystem *) env->GetLongField(obj, getNativeSystemPtrFieldId(env, obj));
}


/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    featureCount
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_featureCount
        (JNIEnv *env, jobject obj)
{
    jlong count = 0;
    try {
        count = (jlong)(nativeSystem(env, obj)->featureCount());
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    return count;
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    speakerCount
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_speakerCount
        (JNIEnv *env, jobject obj)
{
    jlong count = 0;
    try {
        count = (jlong)(nativeSystem(env, obj)->speakerCount());
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    return count;
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    isUBMLoaded
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_isUBMLoaded
        (JNIEnv *env, jobject obj)
{
    jboolean isLoaded = JNI_FALSE;
    try {
        isLoaded = (jboolean)(nativeSystem(env, obj)->isUBMLoaded());
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    return isLoaded;
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    speakerIDs
 * Signature: ()[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_speakerIDs
        (JNIEnv *env, jobject obj)
{
    std::vector<String> speakerIds;
    try {
        speakerIds = nativeSystem(env,obj)->speakerIDs();
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
        return NULL;
    }

    jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray result = env->NewObjectArray(speakerIds.size(), stringClass, env->NewStringUTF(""));
    for (int i=0; i<speakerIds.size(); i++)
    {
        env->SetObjectArrayElement(result, i, env->NewStringUTF(speakerIds[i].c_str()));
    }
    env->DeleteLocalRef(stringClass);
    return result;
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    setOption
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_setOption
        (JNIEnv *env, jobject obj, jstring jOptionName, jstring jOptionValue)
{
    const char* optionName = env->GetStringUTFChars(jOptionName, NULL);
    const char* optionValue = env->GetStringUTFChars(jOptionValue, NULL);
    try {
        nativeSystem(env,obj)->setOption(optionName, optionValue);
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    env->ReleaseStringUTFChars(jOptionName, optionName);
    env->ReleaseStringUTFChars(jOptionValue, optionValue);
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    decisionThreshold
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_decisionThreshold
        (JNIEnv *env, jobject obj)
{
    jdouble decisionThreshold = 0;
    try {
        decisionThreshold = (jdouble)(nativeSystem(env, obj)->decisionThreshold());
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    return decisionThreshold;
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    setDecisionThreshold
 * Signature: (D)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_setDecisionThreshold
        (JNIEnv *env, jobject obj, jdouble newValue)
{
    try {
        (nativeSystem(env, obj)->setDecisionThreshold(newValue));
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    addAudio
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_addAudio___3B
        (JNIEnv *env, jobject obj, jbyteArray jData)
{
    long dataSize = env->GetArrayLength(jData);
    jbyte *data = env->GetByteArrayElements(jData, NULL);
    try {
        nativeSystem(env,obj)->addAudio((uint32_t )dataSize, (void*)data);
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    env->ReleaseByteArrayElements(jData, data, JNI_ABORT);
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    addAudio
 * Signature: ([S)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_addAudio___3S
        (JNIEnv *env, jobject obj, jshortArray jSamples)
{
    long sampleCount = env->GetArrayLength(jSamples);
    jshort *samples = env->GetShortArrayElements(jSamples, NULL);
    try {
        nativeSystem(env,obj)->addAudio((uint32_t )sampleCount, (int16_t*)samples);
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    env->ReleaseShortArrayElements(jSamples, samples, JNI_ABORT);
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    addAudio
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_addAudio__Ljava_lang_String_2
        (JNIEnv *env, jobject obj, jstring jFilename)
{
    const char* filename = env->GetStringUTFChars(jFilename, NULL);
    try {
        nativeSystem(env,obj)->addAudio(filename);
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    env->ReleaseStringUTFChars(jFilename, filename);
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    saveAudio
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_saveAudio
        (JNIEnv *env, jobject obj, jstring jFilename)
{
    const char* filename = env->GetStringUTFChars(jFilename, NULL);
    try {
        nativeSystem(env,obj)->saveAudio(filename);
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    env->ReleaseStringUTFChars(jFilename, filename);
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    resetAudio
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_resetAudio
        (JNIEnv *env, jobject obj)
{
    try {
        nativeSystem(env,obj)->resetAudio();
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    addFeatures
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_addFeatures___3B
        (JNIEnv *env, jobject obj, jbyteArray jData)
{
    long dataSize = env->GetArrayLength(jData);
    jbyte *data = env->GetByteArrayElements(jData, NULL);
    try {
        nativeSystem(env,obj)->addFeatures(dataSize, (uint8_t*)data);
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    env->ReleaseByteArrayElements(jData, data, JNI_ABORT);
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    addFeatures
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_addFeatures__Ljava_lang_String_2
        (JNIEnv *env, jobject obj, jstring jFilename)
{
    const char* filename = env->GetStringUTFChars(jFilename, NULL);
    try {
        nativeSystem(env,obj)->addFeatures(filename);
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    env->ReleaseStringUTFChars(jFilename, filename);
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    saveFeatures
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_saveFeatures
        (JNIEnv *env, jobject obj, jstring jFilename)
{
    const char* filename = env->GetStringUTFChars(jFilename, NULL);
    try {
        nativeSystem(env,obj)->saveFeatures(filename);
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    env->ReleaseStringUTFChars(jFilename, filename);
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    resetFeatures
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_resetFeatures
        (JNIEnv *env, jobject obj)
{
    try {
        nativeSystem(env,obj)->resetFeatures();
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    loadBackgroundModel
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_loadBackgroundModel
        (JNIEnv *env, jobject obj, jstring jFilename)
{
    const char* filename = env->GetStringUTFChars(jFilename, NULL);
    try {
        nativeSystem(env,obj)->loadBackgroundModel(filename);
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    env->ReleaseStringUTFChars(jFilename, filename);
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    loadSpeakerModel
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_loadSpeakerModel
        (JNIEnv *env, jobject obj, jstring jSpeakerId, jstring jFilename)
{
    const char* speakerId = env->GetStringUTFChars(jSpeakerId, NULL);
    const char* filename = env->GetStringUTFChars(jFilename, NULL);
    try {
        nativeSystem(env,obj)->loadSpeakerModel(speakerId,filename);
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    env->ReleaseStringUTFChars(jSpeakerId, speakerId);
    env->ReleaseStringUTFChars(jFilename, filename);
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    saveSpeakerModel
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_saveSpeakerModel
        (JNIEnv *env, jobject obj, jstring jSpeakerId, jstring jFilename)
{
    const char* speakerId = env->GetStringUTFChars(jSpeakerId, NULL);
    const char* filename = env->GetStringUTFChars(jFilename, NULL);
    try {
        nativeSystem(env,obj)->saveSpeakerModel(speakerId,filename);
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    env->ReleaseStringUTFChars(jSpeakerId, speakerId);
    env->ReleaseStringUTFChars(jFilename, filename);
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    removeSpeaker
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_removeSpeaker
        (JNIEnv *env, jobject obj, jstring jSpeakerId)
{
    const char* speakerId = env->GetStringUTFChars(jSpeakerId, NULL);
    try {
        nativeSystem(env,obj)->removeSpeaker(speakerId);
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    env->ReleaseStringUTFChars(jSpeakerId, speakerId);
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    removeAllSpeakers
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_removeAllSpeakers
        (JNIEnv *env, jobject obj)
{
    try {
        nativeSystem(env,obj)->removeAllSpeakers();
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    createSpeakerModel
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_createSpeakerModel
        (JNIEnv *env, jobject obj, jstring jSpeakerId)
{
    const char* speakerId = env->GetStringUTFChars(jSpeakerId, NULL);
    try {
        nativeSystem(env,obj)->createSpeakerModel(speakerId);
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    env->ReleaseStringUTFChars(jSpeakerId, speakerId);
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    adaptSpeakerModel
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_adaptSpeakerModel
        (JNIEnv *env, jobject obj, jstring jSpeakerId)
{
    const char* speakerId = env->GetStringUTFChars(jSpeakerId, NULL);
    try {
        nativeSystem(env,obj)->adaptSpeakerModel(speakerId);
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    env->ReleaseStringUTFChars(jSpeakerId, speakerId);
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    verifySpeaker
 * Signature: (Ljava/lang/String;Z)LAlizeSpkRec/SimpleSpkDetSystem/SpkRecResult;
 */
JNIEXPORT jobject JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_verifySpeaker
        (JNIEnv *env, jobject obj, jstring jSpeakerId, jboolean jAccumulateScores)
{
    const char* speakerId = env->GetStringUTFChars(jSpeakerId, NULL);
    float score;
    bool match;
    try {
        match = nativeSystem(env,obj)->verifySpeaker(speakerId, score, (jAccumulateScores==JNI_TRUE));
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
        env->ReleaseStringUTFChars(jSpeakerId, speakerId);
        return 0;
    }
    env->ReleaseStringUTFChars(jSpeakerId, speakerId);

    jclass resultClass = env->FindClass("AlizeSpkRec/SimpleSpkDetSystem$SpkRecResult");
    jmethodID resultConstructor = env->GetMethodID(resultClass, "<init>", "()V");
    jobject result = env->NewObject(resultClass, resultConstructor);

    jfieldID matchFieldId = env->GetFieldID(resultClass, "match", "Z");
    env->SetBooleanField(result, matchFieldId, (jboolean)match);

    jfieldID scoreFieldId  = env->GetFieldID(resultClass, "score", "F");
    env->SetFloatField(result, scoreFieldId, (jfloat)score);

    jfieldID speakerIdFieldId  = env->GetFieldID(resultClass, "speakerId", "Ljava/lang/String;");
    env->SetObjectField(result, speakerIdFieldId, jSpeakerId);

    env->DeleteLocalRef(resultClass);
    return result;
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    identifySpeaker
 * Signature: (Z)LAlizeSpkRec/SimpleSpkDetSystem/SpkRecResult;
 */
JNIEXPORT jobject JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_identifySpeaker
        (JNIEnv *env, jobject obj, jboolean jAccumulateScores)
{
    String foundSpeakerId;
    float score;
    bool match;
    try {
        match = nativeSystem(env,obj)->identifySpeaker(foundSpeakerId, score, (jAccumulateScores==JNI_TRUE));
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
        return 0;
    }

    jclass resultClass = env->FindClass("AlizeSpkRec/SimpleSpkDetSystem$SpkRecResult");
    jmethodID resultConstructor = env->GetMethodID(resultClass, "<init>", "()V");
    jobject result = env->NewObject(resultClass, resultConstructor);

    jfieldID matchFieldId = env->GetFieldID(resultClass, "match", "Z");
    env->SetBooleanField(result, matchFieldId, (jboolean)match);

    jfieldID scoreFieldId  = env->GetFieldID(resultClass, "score", "F");
    env->SetFloatField(result, scoreFieldId, (jfloat)score);

    jfieldID speakerIdFieldId  = env->GetFieldID(resultClass, "speakerId", "Ljava/lang/String;");
    env->SetObjectField(result, speakerIdFieldId, env->NewStringUTF(foundSpeakerId.c_str()));

    env->DeleteLocalRef(resultClass);
    return result;
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    resetAccumulatedScore
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_resetAccumulatedScore
        (JNIEnv *env, jobject obj, jstring jSpeakerId)
{
    const char* speakerId = env->GetStringUTFChars(jSpeakerId, NULL);
    try {
        nativeSystem(env,obj)->resetAccumulatedScore(speakerId);
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    env->ReleaseStringUTFChars(jSpeakerId, speakerId);
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    resetAllAccumulatedScores
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_resetAllAccumulatedScores
        (JNIEnv *env, jobject obj)
{
    try {
        nativeSystem(env,obj)->resetAllAccumulatedScores();
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    initSystem
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_initSystem
        (JNIEnv *env, jobject obj, jstring jConfigFilename, jstring jWorkdirPath)
{
    const char* workdirPath = env->GetStringUTFChars(jWorkdirPath, NULL);
    const char* configFilename = env->GetStringUTFChars(jConfigFilename, NULL);
    SimpleSpkDetSystem *recognizer;
    try {
        Config config(String(workdirPath) + "/" + String(configFilename));
        recognizer = new SimpleSpkDetSystem(config, workdirPath);
        env->SetLongField(obj, getNativeSystemPtrFieldId(env, obj), (jlong)recognizer);
    } catch(Exception& e) {
        transferExceptionToJava(env, e);
    }
    env->ReleaseStringUTFChars(jConfigFilename, configFilename);
}

/*
 * Class:     AlizeSpkRec_SimpleSpkDetSystem
 * Method:    releaseSystem
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_AlizeSpkRec_SimpleSpkDetSystem_releaseSystem
        (JNIEnv *env, jobject obj)
{
    delete nativeSystem(env, obj);
    env->SetLongField(obj, getNativeSystemPtrFieldId(env, obj), (jlong)NULL);
}

