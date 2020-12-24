package com.emaraic.jdlib;

import com.emaraic.utils.FaceDescriptor;
import com.emaraic.utils.Image;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Collections;

/**
 *
 * @author Taha Emara 
 * Website: http://www.emaraic.com 
 * Email : taha@emaraic.com
 * Created on: Nov 21, 2020
 */
public class Jdlib {

    public Jdlib() {
        loadLib();
    }

    private native long getFaceDectorHandler();

    private native long getShapePredictorHandler(String modelPath);

    private native long getFaceEmbeddingHandler(String modelPath);

    private native ArrayList<Rectangle> faceDetect(long faceDetectorHandler, byte[] pixels, int h, int w);

    private native ArrayList<FaceDescriptor> getFacialLandmarks(long shapePredictorHandler, long faceDetectorHandler, byte[] pixels, int h, int w);

    private native ArrayList<FaceDescriptor> getFaceEmbeddings(long FaceEmbeddingHandler, long shapePredictorHandler, long faceDetectorHandler, byte[] pixels, int h, int w);

    private void loadLib() {
        String os = System.getProperty("os.name").toLowerCase();
        String name = System.mapLibraryName("Jdlib");

        String libpath = "";
        if (os.contains("linux")) {
            libpath = "/native" + File.separator + "linux" + File.separator + name;
        } else if (os.contains("mac")) {
            libpath = "/native" + File.separator + "macosx" + File.separator + name;
        }

        InputStream inputStream = null;
        OutputStream outputStream = null;
        try {
            inputStream = Jdlib.class.getResourceAsStream(libpath);
            File fileOut = File.createTempFile(name, "");

            outputStream = new FileOutputStream(fileOut);
            byte[] buffer = new byte[1024];
            int read = -1;
            while ((read = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, read);
            }
            outputStream.close();
            inputStream.close();
            System.load(fileOut.toString());
        } catch (Exception e) {
            System.err.println("Error During Loading Lib!");
        } finally {
            if (inputStream != null) {
                try {
                    inputStream.close();
                } catch (IOException e) {
                    System.err.println("Error During Closing Input Stream!!");
                }
            }
            if (outputStream != null) {
                try {
                    outputStream.close();
                } catch (IOException e) {
                    System.err.println("Error During Closing Output Stream!!");
                }
            }
        }
    }

    public ArrayList<Rectangle> detectFace(BufferedImage img) {
        Image image = new Image(img);
        ArrayList<Rectangle> data = faceDetect(getFaceDectorHandler(), image.pixels, image.height, image.width);
        if (data == null) {
            System.err.println("Jdlib | detectFace | Null data!!");
            data = new ArrayList<>(Collections.EMPTY_LIST);
        }
        return data;
    }

    public ArrayList<FaceDescriptor> getFaceLandmarks(String modelpath, BufferedImage img) {
        Image image = new Image(img);
        ArrayList<FaceDescriptor> data = getFacialLandmarks(getShapePredictorHandler(modelpath), getFaceDectorHandler(), image.pixels, image.height, image.width);
        if (data == null) {
            System.err.println("Jdlib | getFaceLandmarks | Null data!!");
            data = new ArrayList<>(Collections.EMPTY_LIST);
        }
        return data;
    }

    public ArrayList<FaceDescriptor> getFaceEmbeddings(String embedmodel, String landmarksmodel, BufferedImage img) {
        Image image = new Image(img);
        ArrayList<FaceDescriptor> data = getFaceEmbeddings(getFaceEmbeddingHandler(embedmodel), getShapePredictorHandler(landmarksmodel), getFaceDectorHandler(), image.pixels, image.height, image.width);
        if (data == null) {
            System.err.println("Jdlib | getFaceEmbeddings | Null data!!");
            data = new ArrayList<>(Collections.EMPTY_LIST);
        }
        return data;
    }
}
