#include <jni.h>
/* Header for class com_kevin_java_jni_LRTOverflow */

#ifndef _Included_com_kevin_java_jni_LRTOverflow
#define _Included_com_kevin_java_jni_LRTOverflow

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_kevin_localreferencetableoverflow_LRTOverflow_createLoopThreadCauseLRTOverflow(JNIEnv *env, jclass clazz);


JNIEXPORT jobject JNICALL
Java_com_kevin_localreferencetableoverflow_LRTOverflow_createArrayListCauseLRTOverflow(JNIEnv *env,
                                                                                       jclass clazz);

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved);


#ifdef __cplusplus
}
#endif

#endif
