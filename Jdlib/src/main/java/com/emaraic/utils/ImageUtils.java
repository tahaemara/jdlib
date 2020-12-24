package com.emaraic.utils;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.WindowConstants;

/**
 *
 * @author Taha Emara 
 * Website: http://www.emaraic.com 
 * Email : taha@emaraic.com
 * Created on: Dec 10, 2020
 */
public class ImageUtils {

    private static JFrame frame;
    private static JLabel label;

    public static void drawRectangle(BufferedImage image, Rectangle rectangle) {
        Graphics2D graph = image.createGraphics();
        graph.setColor(Color.GREEN);
        graph.draw(rectangle);
        graph.dispose();
    }

    public static void showImage(BufferedImage image) {
        if (frame == null) {
            frame = new JFrame();
            frame.setTitle("Jdlib Viewer");
            frame.setResizable(false);
            frame.setSize(image.getWidth(), image.getHeight());
            frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
            label = new JLabel();
            label.setIcon(new ImageIcon(image));
            frame.getContentPane().add(label, BorderLayout.CENTER);
            frame.setLocationRelativeTo(null);
            frame.pack();
            frame.setVisible(true);
        } else {
            label.setIcon(new ImageIcon(image));
        }
    }

    public static void drawFaceDescriptor(BufferedImage image, FaceDescriptor facedes) {
    Graphics2D graph = image.createGraphics();
        graph.setColor(Color.GREEN);
        graph.draw(facedes.getFaceBox());
        graph.setColor(Color.RED);
        facedes.getFacialLandmarks().stream().forEach((point) -> {
            graph.fillOval(point.x, point.y, 3, 3);
        });
        graph.dispose();
    }
}
