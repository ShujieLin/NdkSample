/*
#include <jni.h>
#include <string>
extern "C" JNIEXPORT jstring JNICALL

Java_com_shujie_ndksample_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject */
/* this *//*
) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}*/

#include "com_shujie_ndksample_MainActivity.h"
#include <jni.h>
#include <android/log.h>//NDK工具链里面的log库

#define TAG "TestNdk"
#define LOGD (...) __android_log_print(ANDROID_LOG_DEBUG,TAG,_VA_ARGS__);

extern "C"
JNIEXPORT/*用于标记方法，表示可以被外部调用*/ jstring/*java-native代码转换使用的*/ JNICALL/*JNI标记，可以没有*/
Java_com_shujie_ndksample_MainActivity_testJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement testJNI()
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_shujie_ndksample_MainActivity_testStaticJNI(JNIEnv *env, jclass clazz) {
    // TODO: implement testStaticJNI()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_shujie_ndksample_MainActivity_changName(JNIEnv *env, jobject thiz) {
    //获取class
    jclass jClass = env->GetObjectClass(thiz);
    /**
     * MainActivity.class
     * 属性名
     * 属性的签名 'L'代表引用类型
     */
    jfieldID jNameFiledId = env->GetFieldID(jClass, "name", "Ljava/lang/String;");

    //转换为jni层
    jstring jStringName = static_cast<jstring>(env->GetObjectField(thiz, jNameFiledId));

    //转换为native层
    char *cStr = const_cast<char *>(env->GetStringUTFChars(jStringName, NULL));
    //打印
//    LOGD("native:%s",cStr);

    //修改
    env->SetObjectField(thiz, jNameFiledId, env->NewStringUTF("TestNDKSuccessful"));

}
extern "C"
JNIEXPORT void JNICALL
Java_com_shujie_ndksample_MainActivity_changAge(JNIEnv *env, jobject thiz) {
    jclass jClass = env->GetObjectClass(thiz);
    jfieldID jFeildID = env->GetStaticFieldID(jClass, "age", "I");
    jint age = env->GetStaticIntField(jClass, jFeildID);
    env->SetStaticIntField(jClass, jFeildID, 18);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_shujie_ndksample_MainActivity_invokeAddMethod(JNIEnv *env, jobject thiz) {
    jclass jClass = env->GetObjectClass(thiz);
    jmethodID jmethodId = env->GetMethodID(jClass, "addMethod",
                                           "(II)I"/*两个整型参数，一个整型返回值*/);
    jint/*返回值*/ sum =env->CallIntMethod(thiz,jmethodId,1,1/*可变参数*/);
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_shujie_ndksample_MainActivity_invokeAddMethod2(JNIEnv *env, jobject thiz) {
    jclass jClass = env->GetObjectClass(thiz);
    jmethodID jmethodId = env->GetMethodID(jClass, "addMethod",
                                           "(II)I"/*两个整型参数，一个整型返回值*/);
    jint/*返回值*/ sum =env->CallIntMethod(thiz,jmethodId,1,1/*可变参数*/);
    return sum;
}