#include <jni.h>
#include <string>
//#include <thread>
#include <pthread.h>//as上默认有配置
#include <android/log.h>//NDK工具链里面的log库//定义TAG之后，我们可以在LogCat通过TAG过滤出NDK打印的日志

#define TAG "JNITEST"
// 定义info信息
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_shujie_jnithreaddynamic_NativeLib_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JavaVM *javaVm = nullptr;//初始化指针赋值

const char *mainActivityClassName = "com/shujie/jnithreaddynamic/MainActivity";

void dynamicMethod1() {
    LOGD("jni层的dynamicMethod1 被调用");
}

int dynamicMethod2(JNIEnv *env, jobject thiz, jstring valueStr) {
    LOGD("jni层的dynamicMethod2 被调用");
    return 18;
}

const char *javaMethod1 = "dynamicMethod1";

static const JNINativeMethod jniNativeMethod[] = {
        {javaMethod1,      "()V", (void *) dynamicMethod1},
        {"dynamicMethod2", "(Ljava/lang/String;)I",    (int *) dynamicMethod2}
};

//默认会执行JNI_OnLoad
JNIEXPORT jint JNI_OnLoad(JavaVM *javaVmArg, void *) {
    ::javaVm = javaVmArg;

    JNIEnv *jniEnv = nullptr;
    int result = javaVm->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6);
    if (result != JNI_OK) {
        return -1;//crash
    }

    LOGD("jni load init");
    jclass mainActivityClass = jniEnv->FindClass(mainActivityClassName);
    jniEnv->RegisterNatives(mainActivityClass,jniNativeMethod, sizeof(jniNativeMethod) / sizeof(JNINativeMethod));
    LOGD("JNI动态注册完成");

    return JNI_VERSION_1_6;
}

class MyContext{
public:
    jobject  instance = nullptr;
};

void  * myThreadTask(void * pVoid){
    LOGD("myThreadTask had been invoked");

    MyContext * myContext = static_cast<MyContext *>(pVoid);

    JNIEnv * jniEnv = nullptr;// 全新的JNIEnv  异步线程里面操作
    jint attachResult = ::javaVm->AttachCurrentThread(&jniEnv, nullptr);// 附加当前异步线程后，会得到一个全新的 env，此env相当于是子线程专用env
    if (attachResult != JNI_OK){
        return 0;
    }

    jclass mainActivityClass = jniEnv->GetObjectClass(myContext->instance);
    jmethodID  jmethodId_ = jniEnv->GetMethodID(mainActivityClass,"updateActivityUI","()V");
    jniEnv->CallVoidMethod(myContext->instance,jmethodId_);
    ::javaVm->DetachCurrentThread();

    LOGE("C++ 异步线程OK");

    return nullptr;
}

/**
 * JNIEnv不能跨越线程
 * jobject不能跨域线程和函数，可以提升为全局引用解这个决问题
 * JavaVM能够跨越线程和函数
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_shujie_jnithreaddynamic_MainActivity_nativeThread(JNIEnv *env, jobject thiz) {
    /*pthread_t pid;
    pthread_create(&pid, nullptr,myThreadTask, nullptr);
    pthread_join(pid, nullptr);*/

    MyContext * myContext = new MyContext;
    myContext->instance = env->NewGlobalRef(thiz);//提升全局引用

    pthread_t pid;
    pthread_create(&pid, nullptr,myThreadTask, myContext);
    pthread_join(pid, nullptr);
}