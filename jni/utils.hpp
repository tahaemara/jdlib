//
//  utils.hpp
//  Jdlib
//
//  Created by Taha Emara on 11/21/20.
//

#ifndef utils_hpp
#define utils_hpp
#include <iostream>
#include <jni.h>
#include <dlib/image_io.h>

using namespace dlib;


std::string convertJStringtoStdString(JNIEnv *env, jstring jStr);
jclass getJavaClass(JNIEnv *env,std::string classname);
jmethodID getJavaMethod(JNIEnv *env, jclass cls, std::string methdname, std::string methdsig);
jobject convertDlibRectangleToJRectangle(JNIEnv *env, rectangle & rect, jclass Rectangle_Class, jmethodID Rectangle_Constructor);
array2d<rgb_pixel> convertBufferedImageToDlibImage(jbyte* bufferPtr, int h, int w);
#endif /* utils_hpp */
