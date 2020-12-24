//
//  handlers.cpp
//  Jdlib
//
//  Created by Taha Emara on 12/18/20.
//

#include "handlers.hpp"

FaceDetectorHandler::FaceDetectorHandler(){
    face_detector = dlib::get_frontal_face_detector();
}
dlib::frontal_face_detector FaceDetectorHandler::getFaceDetector(){
    return face_detector;
}

FaceDetectorHandler * FaceDetectorHandler::getFaceDetectorHandler(){
    static FaceDetectorHandler *face_detector_handler;
    if (!face_detector_handler)
        face_detector_handler = new FaceDetectorHandler;
    return face_detector_handler;
}



ShapePredictorHandler::ShapePredictorHandler(const std::string & model_path) : model_path(model_path){
    dlib::deserialize(model_path)>>shape_predictor_model;
}

dlib::shape_predictor ShapePredictorHandler::getShapePredictorModel(){
  return shape_predictor_model;
}

ShapePredictorHandler * ShapePredictorHandler::getShapePredictorHandler(const std::string & model_path){
    static ShapePredictorHandler *shape_predictor_handler;
    if (!shape_predictor_handler)
        shape_predictor_handler = new ShapePredictorHandler(model_path);
    return shape_predictor_handler;
}


FaceEmbeddingHandler::FaceEmbeddingHandler(const std::string & model_path) : model_path(model_path){
    dlib::deserialize(model_path)>>face_embedding_model;
}

anet_type FaceEmbeddingHandler::getFaceEmbeddingModel(){
  return face_embedding_model;
}

FaceEmbeddingHandler * FaceEmbeddingHandler::getFaceEmbeddingHandler(const std::string & model_path){
    static FaceEmbeddingHandler *face_embedding_handler;
    if (!face_embedding_handler)
        face_embedding_handler = new FaceEmbeddingHandler(model_path);
    return face_embedding_handler;
}
