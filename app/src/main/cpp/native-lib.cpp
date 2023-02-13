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

#include <jni.h>
#include <string>
#include "com_shujie_ndksample_MainActivity.h"
#include <android/log.h>//NDK工具链里面的log库

//定义TAG之后，我们可以在LogCat通过TAG过滤出NDK打印的日志
#define TAG "JNITEST"
// 定义info信息
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

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
//    ("native:%s",cStr);

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
    jint/*返回值*/ sum = env->CallIntMethod(thiz, jmethodId, 1, 1/*可变参数*/);
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_shujie_ndksample_MainActivity_invokeAddMethod2(JNIEnv *env, jobject thiz) {
    jclass jClass = env->GetObjectClass(thiz);
    jmethodID jmethodId = env->GetMethodID(jClass, "addMethod",
                                           "(II)I"/*两个整型参数，一个整型返回值*/);
    jint/*返回值*/ sum = env->CallIntMethod(thiz, jmethodId, 1, 1/*可变参数*/);
    return sum;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_shujie_ndksample_MainActivity_testArrayAction(JNIEnv *env, jobject thiz, jintArray ints,
                                                       jobjectArray strs) {
    jint *jintArray = env->GetIntArrayElements(ints, NULL);
    jsize jSize = env->GetArrayLength(ints);

    for (int i = 0; i < jSize; ++i) {
        *(jintArray+i) += 1;
    }

    /**
     * 0：刷新java数组，并释放C++层数组
     * JNI_COMMIT:刷新java数组，不释放c++层数组
     * JNI_ABORT:只释放c++层数组
     */
    env->ReleaseIntArrayElements(ints, jintArray, 0);
    for (int i = 0; i < jSize; ++i) {
        LOGI("jni 层打印：整型参数 = %d", *(jintArray + i));
    }

    //修改java的对象引用
    jsize strSize =env->GetArrayLength(ints);
    for (int i = 0; i < strSize; ++i) {
        jstring jString = static_cast<jstring>(env->GetObjectArrayElement(strs, i));
        const char* jElement = env->GetStringUTFChars(jString,NULL);
        env->ReleaseStringUTFChars(jString,jElement);
        LOGI("jni 层打印：String参数 = %s", jElement);
    }

}
extern "C"
JNIEXPORT void JNICALL
Java_com_shujie_ndksample_MainActivity_changPerson(JNIEnv *env, jobject thiz, jobject person,
                                                   jstring name, jint age) {
    jclass  jClass = env->GetObjectClass(person);

    jmethodID  jMethodIdsetName = env->GetMethodID(jClass,"setName", "(Ljava/lang/String;)V");
    jmethodID  jmethodIdSetAge =  env->GetMethodID(jClass,"setAge", "(I)V");

    //调用方法
    env->CallVoidMethod(person,jMethodIdsetName,name);
    env->CallVoidMethod(person,jmethodIdSetAge,age);
}
extern "C"
JNIEXPORT jobject JNICALL
Java_com_shujie_ndksample_MainActivity_newPerson(JNIEnv *env, jobject thiz) {
//    const char* pe
    const char* c = "com/shujie/ndksample/Person";
    jclass  jClass = env->FindClass(c);
    jobject jPerson =env->AllocObject(jClass);//实例化对象，但是不调用构造函数

    jmethodID  jMethodIdsetName = env->GetMethodID(jClass,"setName", "(Ljava/lang/String;)V");
    jmethodID  jmethodIdSetAge =  env->GetMethodID(jClass,"setAge", "(I)V");

    //调用方法
    jstring jString = env->NewStringUTF("person object");
    env->CallVoidMethod(jPerson,jMethodIdsetName,jString);
    env->CallVoidMethod(jPerson,jmethodIdSetAge,1);
    return jPerson;
}