#include <jni.h>
#include <string>
#include <android/log.h>
extern "C" {
#include<libavcodec/avcodec.h>
#include <ffmpeg.c>

#define TAG "ZODemo-jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型
}

void custom_log(void *ptr, int level, const char* fmt, va_list vl){

    FILE *fp=fopen("/sdcard/rollcap/av_log.txt","a+");
    if(fp){
        vfprintf(fp,fmt,vl);
        fflush(fp);
        fclose(fp);
    }
}

extern "C"
jstring
Java_com_example_gzx_cmakeffmpeg_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(avcodec_configuration());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_gzx_cmakeffmpeg_MainActivity_ffmpegMain(JNIEnv *env, jobject object, jint cmdnum, jobjectArray cmdline) {
    av_log_set_callback(custom_log);
    int argc=cmdnum;
    LOGE("########## i = %d", cmdnum);
    char** argv=(char**)malloc(sizeof(char*)*argc);

    int i=0;
    for(i=0;i<argc;i++)
    {
        jstring string=env->GetObjectArrayElement(env*,cmdline,i);

        const char* tmp=env->GetStringUTFChars(env*,string,0);
        argv[i]=(char*)malloc(sizeof(char)*1024);
        strcpy(argv[i],tmp);
        LOGE("########## cmd = %s", argv[i]);
    }
    LOGE("########## ffmpegmain begin ");
    return main(argc,argv);
    LOGE("########## ffmpegmain ");
    for(i=0;i<argc;i++){
        free(argv[i]);
    }
    free(argv);

}

