#include"com_emaraic_jdlib_Jdlib.h"


#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include <dlib/image_processing.h>
#include "utils.hpp"
#include "handlers.hpp"


using namespace dlib;
using namespace std;


static jclass ArrayList_Class;
static jmethodID ArrayList_Constructor;
static jmethodID ArrayList_Add;


static jclass Rectangle_Class;
static jmethodID Rectangle_Constructor;

static jclass Point_Class;
static jmethodID Point_Constructor;

static jclass FaceDescriptor_Class;
static jmethodID FaceDescriptor_Constructor;

static jint JNI_VERSION = JNI_VERSION_1_8;


jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION) != JNI_OK) {
        return JNI_ERR;
    }
    
    jclass tempLocalClassRef;
    
    tempLocalClassRef = getJavaClass(env, "java/util/ArrayList");
    ArrayList_Class = (jclass) env->NewGlobalRef(tempLocalClassRef);
    env->DeleteLocalRef(tempLocalClassRef);
    ArrayList_Constructor = getJavaMethod(env, ArrayList_Class, "<init>", "()V");
    ArrayList_Add = getJavaMethod(env, ArrayList_Class, "add", "(Ljava/lang/Object;)Z");
    
    tempLocalClassRef = getJavaClass(env, "java/awt/Rectangle");
    Rectangle_Class = (jclass) env->NewGlobalRef(tempLocalClassRef);
    env->DeleteLocalRef(tempLocalClassRef);
    Rectangle_Constructor = getJavaMethod(env, Rectangle_Class, "<init>", "(IIII)V");
    
    tempLocalClassRef = getJavaClass(env, "java/awt/Point");
    Point_Class = (jclass) env->NewGlobalRef(tempLocalClassRef);
    env->DeleteLocalRef(tempLocalClassRef);
    Point_Constructor =getJavaMethod(env, Point_Class, "<init>", "(II)V");
    
    tempLocalClassRef = getJavaClass(env, "com/emaraic/utils/FaceDescriptor");
    FaceDescriptor_Class = (jclass) env->NewGlobalRef(tempLocalClassRef);
    env->DeleteLocalRef(tempLocalClassRef);
    FaceDescriptor_Constructor = getJavaMethod(env, FaceDescriptor_Class, "<init>", "(Ljava/awt/Rectangle;Ljava/util/ArrayList;[F)V");

    return JNI_VERSION;
}


void JNI_OnUnload(JavaVM *vm, void *reserved) {
    JNIEnv* env;
    vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION);
    env->DeleteGlobalRef(ArrayList_Class);
    env->DeleteGlobalRef(Rectangle_Class);
    env->DeleteGlobalRef(Point_Class);
    env->DeleteGlobalRef(FaceDescriptor_Class);
}


JNIEXPORT jlong JNICALL Java_com_emaraic_jdlib_Jdlib_getFaceDectorHandler
(JNIEnv *env, jobject obj){
    FaceDetectorHandler *face_detector_handler=face_detector_handler->getFaceDetectorHandler();
    
    return (long) face_detector_handler;
}

JNIEXPORT jlong JNICALL Java_com_emaraic_jdlib_Jdlib_getShapePredictorHandler
(JNIEnv *env, jobject obj, jstring model_path){
    ShapePredictorHandler *shape_predictor_handler=shape_predictor_handler->getShapePredictorHandler(convertJStringtoStdString(env, model_path));
     
     return (long) shape_predictor_handler;
}

JNIEXPORT jlong JNICALL Java_com_emaraic_jdlib_Jdlib_getFaceEmbeddingHandler
(JNIEnv *env, jobject obj, jstring model_path){
    FaceEmbeddingHandler *face_embedding_handler=face_embedding_handler->getFaceEmbeddingHandler(convertJStringtoStdString(env, model_path));
     
     return (long) face_embedding_handler;
}



JNIEXPORT jobject JNICALL Java_com_emaraic_jdlib_Jdlib_faceDetect
 (JNIEnv *env , jobject obj, jlong detectorHandler, jbyteArray imgdata, jint h, jint w){
     
       FaceDetectorHandler *face_detector_handler = (FaceDetectorHandler*)detectorHandler;
     dlib::frontal_face_detector detector=face_detector_handler->getFaceDetector();
     
     jbyte* bufferPtr = env->GetByteArrayElements(imgdata,0);
     array2d<rgb_pixel> img=convertBufferedImageToDlibImage(bufferPtr,  h,  w);
     
     std::vector<rectangle> dets = detector(img);
     
     jobject rects_obj = (*env).NewObject(ArrayList_Class, ArrayList_Constructor);
     
     for (int i=0;i<dets.size();i++)
     {
         rectangle rect=dets[i];
         jobject jrect=convertDlibRectangleToJRectangle(env, rect, Rectangle_Class, Rectangle_Constructor);
         env->CallBooleanMethod(rects_obj, ArrayList_Add, jrect);
         
     }
     
     return rects_obj;
 }


JNIEXPORT jobject JNICALL Java_com_emaraic_jdlib_Jdlib_getFacialLandmarks
(JNIEnv *env , jobject obj, jlong shapePredictorHandler, jlong faceDetectorHandler, jbyteArray imgdata, jint h, jint w){
    
      FaceDetectorHandler *face_detector_handler = (FaceDetectorHandler*)faceDetectorHandler;

       dlib::frontal_face_detector detector=face_detector_handler->getFaceDetector();
       
    
    jbyte* bufferPtr = env->GetByteArrayElements(imgdata,0);
    array2d<rgb_pixel> img=convertBufferedImageToDlibImage(bufferPtr,  h,  w);
        
    std::vector<rectangle> faces = detector(img);
    
    ShapePredictorHandler *shape_predictor_handler =(ShapePredictorHandler *)shapePredictorHandler;
    shape_predictor pose_model= shape_predictor_handler->getShapePredictorModel();
    

    jobject face_marks_obj = env->NewObject(ArrayList_Class, ArrayList_Constructor);
    
    for (unsigned long i = 0; i < faces.size(); ++i){
        rectangle rect=faces[i];
        jobject points_obj = env->NewObject(ArrayList_Class, ArrayList_Constructor);
        
        full_object_detection shape=pose_model(img, rect);
        jobject jrect=convertDlibRectangleToJRectangle(env,rect, Rectangle_Class, Rectangle_Constructor);

        for(int j=0; j<shape.num_parts();j++){
            point point=shape.part(j);
            jobject pointobj=env->NewObject(Point_Class, Point_Constructor,(jint)point.x(),(jint)point.y());
            jboolean st=env->CallBooleanMethod(points_obj, ArrayList_Add, pointobj);
            env->DeleteLocalRef(pointobj);
        }
        
        jobject face_des_obj=env->NewObject(FaceDescriptor_Class, FaceDescriptor_Constructor, jrect, points_obj, nullptr);
        jboolean f=env->CallBooleanMethod(face_marks_obj, ArrayList_Add, face_des_obj);
        env->DeleteLocalRef(face_des_obj);
    }
    
    return face_marks_obj;
}



JNIEXPORT jobject JNICALL Java_com_emaraic_jdlib_Jdlib_getFaceEmbeddings
(JNIEnv *env , jobject obj, jlong faceEmbeddingHandler, jlong shapePredictorHandler, jlong faceDetectorHandler, jbyteArray imgdata, jint h, jint w){
    
      FaceDetectorHandler *face_detector_handler = (FaceDetectorHandler*)faceDetectorHandler;

       dlib::frontal_face_detector detector=face_detector_handler->getFaceDetector();
       
    
    jbyte* bufferPtr = env->GetByteArrayElements(imgdata,0);
    array2d<rgb_pixel> img=convertBufferedImageToDlibImage(bufferPtr,  h,  w);
        
    std::vector<rectangle> faces = detector(img);
    
    ShapePredictorHandler *shape_predictor_handler =(ShapePredictorHandler *)shapePredictorHandler;
    shape_predictor pose_model= shape_predictor_handler->getShapePredictorModel();
    
    
    FaceEmbeddingHandler *face_embedding_handler =(FaceEmbeddingHandler *)faceEmbeddingHandler;
    anet_type face_embedding_model= face_embedding_handler->getFaceEmbeddingModel();
    
    
    jobject faces_descriptor = env->NewObject(ArrayList_Class, ArrayList_Constructor);

    for (unsigned long i = 0; i < faces.size(); ++i){
        rectangle rect=faces[i];
        jobject points_obj = env->NewObject(ArrayList_Class, ArrayList_Constructor);
        
        full_object_detection shape=pose_model(img, rect);
        jobject jrect=convertDlibRectangleToJRectangle(env,rect, Rectangle_Class, Rectangle_Constructor);

        for(int j=0; j<shape.num_parts();j++){
            point point=shape.part(j);
            jobject pointobj=env->NewObject(Point_Class, Point_Constructor,(jint)point.x(),(jint)point.y());
            jboolean st=env->CallBooleanMethod(points_obj, ArrayList_Add, pointobj);
            env->DeleteLocalRef(pointobj);
        }
        
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
        
        matrix<float,0,1> face_embedding = face_embedding_model(face_chip);
        

        
        std::unique_ptr<float[]>  face_emb=face_embedding.steal_memory();
        
        jfloatArray jemb;
        jemb = env->NewFloatArray(128);
        if (jemb == NULL) {
            return NULL;
        }
        env->SetFloatArrayRegion(jemb, 0, 128, face_emb.get());
        
        jobject face_des_obj=env->NewObject(FaceDescriptor_Class, FaceDescriptor_Constructor, jrect, points_obj, jemb);
        jboolean f=env->CallBooleanMethod(faces_descriptor, ArrayList_Add, face_des_obj);
        
        env->DeleteLocalRef(jemb);
        env->DeleteLocalRef(face_des_obj);

    }
    
    return faces_descriptor;
}
