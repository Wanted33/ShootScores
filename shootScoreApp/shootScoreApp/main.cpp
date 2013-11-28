//
//  main.cpp
//  shootScores
//
//  Created by Quentin RUBINI on 27/11/2013.
//  Copyright (c) 2013 Quentin RUBINI. All rights reserved.
//

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


RNG rng(12345);
int cibleX;
int cibleY;
float aire;

void openImg(){
    
    //on tente d’ouvrir"MyPic.JPG" et de le stocker dans “img”
    //    Mat img = imread("/Users/x-quentin33/Desktop/cible2.jpg", CV_LOAD_IMAGE_UNCHANGED);
    Mat img = imread("/Users/x-quentin33/Documents/applications mobiles/Innovation/shootScoreApp/shootScoreApp/carton10.jpg", CV_LOAD_IMAGE_UNCHANGED);
    
    
    if (img.empty()) {
        
        //on vérifie que l’image a bien été chargée
        cout << "failed to load input image\n";
        //        return -1;
        
    }
    
    Mat img2;
    
    cvtColor(img, img2, CV_RGB2GRAY);
    GaussianBlur(img2,img2,Size(9,9),2,2);
    
    //Test Recherche de visuel
    
    vector<Vec3f> circles;
    
    //    HoughCircles(img, circles, CV_HOUGH_GRADIENT, 1, img.rows, 200, 100, 0, 0 );
    HoughCircles(img2, circles, CV_HOUGH_GRADIENT, 1, 1, 200, 100);
    
    cout << "Visuel : " << circles.size() << endl;
    
    //Test impacts
    
    vector<Vec3f> impacts;
    HoughCircles(img2, impacts, CV_HOUGH_GRADIENT, 1, 1, 200, 100, 1, 20);
    
    
    
    
    
    /// Draw the circles detected
    //    if(circles.size() == 1)
    //      {
    //        Point center(cvRound(circles[0][0]), cvRound(circles[0][1]));
    //        float radius = cvRound(circles[0][2]);
    //        // circle center
    //        circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );
    //        circle( img2, center, 3, Scalar(0,255,0), -1, 8, 0 );
    //        // circle outline
    //        circle( img, center, radius, Scalar(0,0,255), 3, 8, 0 );
    //        circle( img2, center, radius, Scalar(0,0,255), 3, 8, 0 );
    //
    //        //test
    //        float coefficient = radius/59.5;
    //        float radius8 = 43.5*coefficient;
    //        float radius9 = 27.5*coefficient;
    //        float radius10 = 11.5*coefficient;
    //
    //        float radius6 = 75.5*coefficient;
    //        float radius5 = 91.5*coefficient;
    //        float radius4 = 107.5*coefficient;
    //        float radius3 = 123.5*coefficient;
    //        float radius2 = 139.5*coefficient;
    //        float radius1 = 155.5*coefficient;
    //
    //        circle(img, center, radius8, Scalar(0, 0, 255));
    //        circle(img, center, radius9, Scalar(0, 0, 255));
    //        circle(img, center, radius10, Scalar(0, 0, 255));
    //
    //        circle(img, center, radius6, Scalar(0, 0, 255));
    //        circle(img, center, radius5, Scalar(0, 0, 255));
    //        circle(img, center, radius4, Scalar(0, 0, 255));
    //        circle(img, center, radius3, Scalar(0, 0, 255));
    //        circle(img, center, radius2, Scalar(0, 0, 255));
    //        circle(img, center, radius1, Scalar(0, 0, 255));
    //
    //    }
    
    
    
//    cout << "Nombres impacts : " << impacts.size() << endl;
//    
//    for( size_t i = 0; i < impacts.size(); i++ )
//    {
//        Point center(cvRound(impacts[i][0]), cvRound(impacts[i][1]));
//        float radius = cvRound(impacts[i][2]);
//        // circle center
//        circle( img, center, 3, Scalar(107,255,112), -1, 8, 0 );
//        // circle outline
//        circle( img, center, radius, Scalar(107,255,112), 3, 8, 0 );
//    }
    
    
    
    
    //    //Recherche des impacts en utilisant la fonction findContours
    //    Mat canny_output;
    //    vector<vector<Point> > contours;
    //    vector<Vec4i> hierarchy;
    //
    //    /// Detect edges using canny
    //    Canny( img2, img2, 100, 100*2, 3 );
    //    /// Find contours
    //    findContours( img2, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    //
    //    /// Draw contours
    //    Mat drawing = Mat::zeros( img.size(), CV_8UC3 );
    //    for( int i = 0; i< contours.size(); i++ )
    //    {
    //
    //        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    //        drawContours( img, contours, i, color, 2, 8, hierarchy, 0, Point() );
    //    }
    //
    //    /// Show in a window
    //    namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    //    imshow( "Contours", drawing );
    //
    
    
    //création fenêtre
    
    namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
    namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
    
    //on affiche 'img' in the "MyWindow" window
    imshow("MyWindow", img2);
    imshow("Original Image", img);
    
    
    
    //attente input clavier
    waitKey(0);
    
    // libère "MyWindow"
    destroyWindow("MyWindow");
}

int main( int argc, const char** argv ) {
    
    openImg();
    
    
    return 0;
}

