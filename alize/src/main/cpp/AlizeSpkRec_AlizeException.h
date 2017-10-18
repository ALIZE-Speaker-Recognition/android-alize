#ifndef ANDROID_ALIZE_ALIZESPKREC_ALIZEEXCEPTION_H
#define ANDROID_ALIZE_ALIZESPKREC_ALIZEEXCEPTION_H

#include <jni.h>
#include "alize.h"

void transferExceptionToJava(JNIEnv * env, alize::Exception& e);

#endif //ANDROID_ALIZE_ALIZESPKREC_ALIZEEXCEPTION_H
