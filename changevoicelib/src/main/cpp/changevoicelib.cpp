#include <com_shujie_changevoicelib_ChangeVoiceActivity.h>
#include <unistd.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_shujie_changevoicelib_ChangeVoiceActivity_voiseChangeNative(JNIEnv *env, jobject thiz,
                                                                     jint mode,
                                                                     jstring path) {
    char *content_ = "default ： play finished";
    const char * path_ = env->GetStringUTFChars(path, NULL);

    FMOD::System *system = 0;
    FMOD::Sound *sound = 0;
    FMOD::Channel *channel = 0;
    FMOD::DSP *dsp = 0;

    FMOD::System_Create(&system);
    system->init(32, FMOD_INIT_NORMAL, 0);

    system->createSound(path_, FMOD_DEFAULT, 0, &sound);

    system->playSound(sound, 0, false, &channel);

    switch (mode) {
        case com_shujie_changevoicelib_ChangeVoiceActivity_MODE_NOMAL:
            content_ = "原声";
            break;
        case com_shujie_changevoicelib_ChangeVoiceActivity_MODE_LUOLI:
            content_ = "萝莉音";
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT,&dsp);
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,3.0f);
            channel->addDSP(0,dsp);
            break;
        default:
            break;
    }

    bool isPlay = true;
    while (isPlay) {
        channel->isPlaying(&isPlay);
        usleep(1000 * 1000);
    }

    sound->release();
    system->close();
    system->release();
    env->ReleaseStringUTFChars(path, path_);

    jclass jclass_ = env->GetObjectClass(thiz);
    jmethodID jmethodId_ = env->GetMethodID(jclass_,"playEndTips", "(Ljava/lang/String;)V");
    jstring contentValue = env->NewStringUTF(content_);
    env->CallVoidMethod(thiz,jmethodId_,contentValue);
}