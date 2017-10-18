#include "AlizeSpkRec_AlizeException.h"


void transferExceptionToJava(JNIEnv * env, alize::Exception& e)
{
    env->ThrowNew(env->FindClass("AlizeSpkRec/AlizeException"), e.toString().c_str());
}
