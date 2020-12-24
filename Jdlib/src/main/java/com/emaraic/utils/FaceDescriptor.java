package com.emaraic.utils;

import java.awt.Point;
import java.awt.Rectangle;
import java.util.ArrayList;

/**
 *
 * @author Taha Emara
 * Website: http://www.emaraic.com
 * Email  : taha@emaraic.com
 * Created on: Dec 12, 2020 
 */
public class FaceDescriptor {

    private final Rectangle faceBox;
    private final ArrayList<Point> facialLandmarks;
    private final float[] faceEmbedding;
    private String label;

    public FaceDescriptor(Rectangle faceBoxes, ArrayList<Point> facialLandmarks) {
        this.faceBox = faceBoxes;
        this.facialLandmarks = facialLandmarks;
        this.faceEmbedding = null;
    }

    
    public FaceDescriptor(Rectangle faceBoxes, ArrayList<Point> facialLandmarks, float[] faceEmbedding) {
        this.faceBox = faceBoxes;
        this.facialLandmarks = facialLandmarks;
        this.faceEmbedding = faceEmbedding;
        this.label = "None";
    }

    public Rectangle getFaceBox() {
        return faceBox;
    }

    public ArrayList<Point> getFacialLandmarks() {
        return facialLandmarks;
    }

    public float[] getFaceEmbedding() {
        return faceEmbedding;
    }

    public String getLabel() {
        return label;
    }

    public void setLabel(String label) {
        this.label = label;
    } 

}
