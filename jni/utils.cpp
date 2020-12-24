//
//  utils.cpp
//  Jdlib
//
//  Created by Taha Emara on 11/21/20.
//

#include "utils.hpp"


std::string convertJStringtoStdString(JNIEnv *env, jstring jstr) {
    if (!jstr)
        return "";
    
    const jclass j_string_class = env->GetObjectClass(jstr);
    const jmethodID getBytes = getJavaMethod(env, j_string_class, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jstr, getBytes, env->NewStringUTF("UTF-8"));
    
    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);
    
    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);
    
    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(j_string_class);
    return ret;
}

jclass getJavaClass(JNIEnv *env, std::string classname){
    jclass cls= env->FindClass(classname.c_str());
    if (env->ExceptionCheck()){
        env->ExceptionClear();
        std::cerr<< "Can't find class: " <<classname<<std::endl;
    }
    return cls;
}

jmethodID getJavaMethod(JNIEnv *env, jclass cls, std::string methdname, std::string methdsig){
    jmethodID method= env->GetMethodID(cls, methdname.c_str(), methdsig.c_str());
    if (env->ExceptionCheck()){
        env->ExceptionClear();
        std::cerr<< "Can't find method: " << methdname<<" with signature: "<<methdsig<<std::endl;}
    return method;
}

jobject convertDlibRectangleToJRectangle(JNIEnv *env, rectangle & rect, jclass Rectangle_Class, jmethodID Rectangle_Constructor){
    jint top_left_x = rect.tl_corner().x();
    jint top_left_y = rect.tl_corner().y();
    jint buttom_right_x = rect.br_corner().x();
    jint buttom_right_y = rect.br_corner().y();
    jobject rect_obj=env->NewObject(Rectangle_Class, Rectangle_Constructor,top_left_x,top_left_y,buttom_right_x-top_left_x,buttom_right_y-top_left_y);
    return rect_obj;
}

array2d<rgb_pixel> convertBufferedImageToDlibImage(jbyte* bytedata, int h, int w){
    array2d<rgb_pixel> img(h,w);
    
    for (int x = 0; x < w; ++x){
        for (int y = 0; y < h ; ++y)
        {
            int pos = (y * 3 * w) + (x * 3);
            rgb_pixel p;
            p.blue = bytedata[pos++] & 0xFF;
            p.green = bytedata[pos++] & 0xFF;
            p.red = bytedata[pos++] & 0xFF;
            assign_pixel(img[y][x],p);
        }
    }
    
    return img;
}
