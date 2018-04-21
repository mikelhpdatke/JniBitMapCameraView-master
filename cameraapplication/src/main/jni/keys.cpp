#include <jni.h>

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_zxing_cameraapplication_MainActivity_argbToabgr(JNIEnv *env, jobject instance,
                                                         jbyteArray buffer_, jint width,
                                                         jint height) {
    jbyte *buffer = env->GetByteArrayElements(buffer_, 0);
    
    int newsize = width * height;
    int a, r, g, b;
    int x = 0, y = 0;
    for(x = 0; x < width; x++){
        for(y = 0; y < height; y++){
            int color = buffer[y * width + x];

            a = (color >> 24) & 0xFF;
            r = (color >> 16) & 0xFF;
            g = (color >> 8) & 0xFF;
            b = color & 0xFF;

            int newColor = (a << 24) | (b << 16) | (g << 8) | r;
            buffer[y * width + x] = newColor;
        }
    }

    jbyteArray result = env -> NewByteArray(newsize);
    env -> SetByteArrayRegion(result , 0, newsize, buffer);

    env -> ReleaseByteArrayElements(buffer_, buffer, 0);
    return result;
}