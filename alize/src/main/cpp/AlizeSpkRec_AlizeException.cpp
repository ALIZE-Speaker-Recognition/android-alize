#include "AlizeSpkRec_AlizeException.h"
#include <map>

using namespace std;

void transferExceptionToJava(JNIEnv * env, alize::Exception& e)
{
    map<string, string> exceptions;
    exceptions["Exception"] = "AlizeSpkRec/AlizeException"; //default
    exceptions["IndexOutOfBoundsException"] = "AlizeSpkRec/AlizeException";
    exceptions["IOException"] = "java/io/IOException";
    exceptions["IdAlreadyExistsException"] = "AlizeSpkRec/IdAlreadyExistsException";
    exceptions["InvalidDataException"] = "AlizeSpkRec/InvalidDataException";
    exceptions["FileNotFoundException"] = "java/io/FileNotFoundException";
    exceptions["EOFException"] = "java/io/EOFException";
    exceptions["OutOfMemoryException"] = "AlizeSpkRec/OutOfMemoryException";
    exceptions["ParamNotFoundInConfigException"] = "AlizeSpkRec/ParamNotFoundInConfigException";
    exceptions["ConfigCheckException"] = "AlizeSpkRec/ConfigCheckException";

    string className = e.getClassName().c_str();

    env->ThrowNew(env->FindClass(exceptions[className].c_str()), e.toString().c_str());
}
