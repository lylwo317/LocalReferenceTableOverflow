#include <iostream>
#include <jni.h>
#include <thread>
#include "LRTOverflow.h"

#ifdef __cplusplus
extern "C" {
#endif

JavaVM *javaVM;

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    javaVM = vm;
    //init();
    return JNI_VERSION_1_4;
}

/**
 * 打印当前所有引用表
 * @param env
 */
static void printDumpReferenceTables(JNIEnv *env) {
    jclass vm_class = env->FindClass("dalvik/system/VMDebug");
    jmethodID dump_mid = env->GetStaticMethodID(vm_class, "dumpReferenceTables", "()V");
    env->CallStaticVoidMethod(vm_class, dump_mid);
    env->DeleteLocalRef(vm_class);
}

static std::thread *t1;
int count;

static void call_from_thread() {
    JNIEnv *env;
    if (javaVM->AttachCurrentThread(&env, NULL) != JNI_OK) {
        return;
    }
    std::string hello("Hello");
    while (1) {
        jstring element = env->NewStringUTF(hello.c_str());
        //env->DeleteLocalRef(element);//手动删除局部引用可以避免local reference table overflow
    }
    printDumpReferenceTables(env);
}
void JNICALL
Java_com_kevin_localreferencetableoverflow_LRTOverflow_createLoopThreadCauseLRTOverflow(JNIEnv *env,
                                                                                        jclass clazz) {
    t1 = new std::thread(call_from_thread);//创建并执行一个子线程
    //printDumpReferenceTables(env);
}

JNIEXPORT jobject JNICALL
Java_com_kevin_localreferencetableoverflow_LRTOverflow_createArrayListCauseLRTOverflow(JNIEnv *env,
                                                                                       jclass clazz) {
    jclass java_util_ArrayList_class;
    jmethodID java_util_ArrayList_;
    jmethodID java_util_ArrayList_add;

    java_util_ArrayList_class = env->FindClass("java/util/ArrayList");
    java_util_ArrayList_     = env->GetMethodID(java_util_ArrayList_class, "<init>", "()V");
    java_util_ArrayList_add  = env->GetMethodID(java_util_ArrayList_class, "add", "(Ljava/lang/Object;)Z");
    jobject result = env->NewObject(java_util_ArrayList_class, java_util_ArrayList_);
    for (int i=0; i <= 1000; i++) {
        std::string hello("Hello");
        hello.append(std::to_string(i));
        jstring element = env->NewStringUTF(hello.c_str());
        env->CallBooleanMethod(result, java_util_ArrayList_add, element);
        //env->DeleteLocalRef(element);//手动删除局部引用可以避免local reference table overflow
    }
    //printDumpReferenceTables(env);
    return result;
}




#ifdef __cplusplus
}
#endif