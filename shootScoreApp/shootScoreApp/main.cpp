//
//  Created by Quentin RUBINI on 27/11/2013.
//  Copyright (c) 2013 Quentin RUBINI. All rights reserved.
//

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;


/*---------- Déclarations de variables ----------*/

RNG rng(12345);
int limiteX;
int limiteY;
int coupsTotal = 0;
int scoreTotal = 0;
int valeurCoup = 0;
int marginTop = 0;
float distanceImpact;
float distanceLimite;
float rayon1;
float rayon2;
float rayon3;
float rayon4;
float rayon5;
float rayon6;
float rayon7;
float rayon8;
float rayon9;
float rayon10;
float coefficient;

/*---------- Fonction qui analyse l'image ----------*/

void openImg(){
    
    //On ouvre l'image et on la stock dans "img"
    Mat img = imread("/Users/x-quentin33/Documents/applications mobiles/Innovation/shootScoreApp/shootScoreApp/carton10.jpg", CV_LOAD_IMAGE_UNCHANGED);
    
    if (img.empty()) {
        
        //on vérifie que l’image a bien été chargée
        cout << "failed to load input image\n";
        //        return -1;
    }
    
    Mat img2;
    
    cvtColor(img, img2, CV_RGB2GRAY);
    GaussianBlur(img2,img2,Size(9,9),2,2);
    
    /*---------- Recherche du visuel ----------*/
    
    vector<Vec3f> circles;
    
    HoughCircles(img2, circles, CV_HOUGH_GRADIENT, 1, 1, 200, 100, 0, 0);
    
    cout << "Visuel : " << circles.size() << endl;
    
    //Fenetre des scores
    Mat pic = cv::Mat::zeros(250,500,CV_8UC3);
    
    //Draw the circles detected
    if(circles.size() == 1)
    {
        Point center(cvRound(circles[0][0]), cvRound(circles[0][1]));
        float radius7 = cvRound(circles[0][2]);
        // circle center
        //        circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );
        circle( img2, center, 3, Scalar(0,255,0), -1, 8, 0 );
        // circle outline
        //        circle( img, center, radius7, Scalar(0,0,255), 3, 8, 0 );
        circle( img2, center, radius7, Scalar(0,0,255), 3, 8, 0 );
        
        //On affecte les différentes valeurs aux variables
        coefficient = radius7/59.5;
        rayon1 = 155.5*coefficient;
        rayon2 = 139.5*coefficient;
        rayon3 = 123.5*coefficient;
        rayon4 = 107.5*coefficient;
        rayon5 = 91.5*coefficient;
        rayon6 = 75.5*coefficient;
        rayon7 = radius7;
        rayon8 = 43.5*coefficient;
        rayon9 = 27.5*coefficient;
        rayon10 = 11.5*coefficient;
        
        //On dessine les différents cercles correspondant aux différentes zones de points
        circle(img, center, rayon8, Scalar(0, 0, 255));
        circle(img, center, rayon9, Scalar(0, 0, 255));
        circle(img, center, rayon10, Scalar(0, 0, 255));
        
        circle(img, center, rayon6, Scalar(0, 0, 255));
        circle(img, center, rayon5, Scalar(0, 0, 255));
        circle(img, center, rayon4, Scalar(0, 0, 255));
        circle(img, center, rayon3, Scalar(0, 0, 255));
        circle(img, center, rayon2, Scalar(0, 0, 255));
        circle(img, center, rayon1, Scalar(0, 0, 255));
        
        //On sauvegarde les coordonnées du centre de notre cible
        limiteX = center.x;
        limiteY = center.y;
    }
    
    /*---------- Recherche des impacts ----------*/
    
    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    /// Detect edges using Threshold
    threshold( img2, threshold_output, 100, 255, THRESH_BINARY );
    /// Find contours
    findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    
    /// Find the rotated rectangles and ellipses for each contour
    vector<RotatedRect> minRect( contours.size() );
    vector<RotatedRect> minEllipse( contours.size() );
    
    for( int i = 0; i < contours.size(); i++ )
    {
        if( contours[i].size() > 5 )
        {
            minEllipse[i] = fitEllipse( Mat(contours[i]) );
        }
    }
    
    /// Draw contours + rotated rects + ellipses
    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        //On vérifie que nos ellipse ne soit pas plus grande que 30
        if (minEllipse[i].size.width < 30) {
            
            //On vérifie que l'ellipse soit dans la zone dans la cible à propement parlé (au minimum c'est un 1)
            if (sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2)) < rayon1)
            {
                
                Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
                // contour
                drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
                // ellipse
                ellipse( drawing, minEllipse[i], color, 2, 8 );
                
                coupsTotal ++;
                valeurCoup = 0;
                
                //Calcul des points
                if (((sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) < rayon1) && ((sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) > rayon2))
                {
                    cout << "coup " << coupsTotal << " : " << " 1 " << endl;
                    scoreTotal += 1;
                    valeurCoup = 1;
                }
                else if (((sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) < rayon2) && (sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) > rayon3)
                {
                    cout << "coup " << coupsTotal << " : " << " 2 " << endl;
                    scoreTotal += 2;
                    valeurCoup = 2;
                }
                else if (((sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) < rayon3) && (sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) > rayon4)
                {
                    cout << "coup " << coupsTotal << " : " << " 3 " << endl;
                    scoreTotal += 3;
                    valeurCoup = 3;
                }
                else if (((sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) < rayon4) && (sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) > rayon5)
                {
                    cout << "coup " << coupsTotal << " : " << " 4 " << endl;
                    scoreTotal += 4;
                    valeurCoup = 4;
                }
                else if (((sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) < rayon5) && (sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) > rayon6)
                {
                    cout << "coup " << coupsTotal << " : " << " 5 " << endl;
                    scoreTotal += 5;
                    valeurCoup = 5;
                }
                else if (((sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) < rayon6) && (sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) > rayon7)
                {
                    cout << "coup " << coupsTotal << " : " << " 6 " << endl;
                    scoreTotal += 6;
                    valeurCoup = 6;
                }
                else if (((sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) < rayon7) && (sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) > rayon8)
                {
                    cout << "coup " << coupsTotal << " : " << " 7 " << endl;
                    scoreTotal += 7;
                    valeurCoup = 7;
                }
                else if (((sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) < rayon8) && (sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) > rayon9)
                {
                    cout << "coup " << coupsTotal << " : " << " 8 " << endl;
                    scoreTotal += 8;
                    valeurCoup = 8;
                }
                else if (((sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2))-(4.5*coefficient)) < rayon9) && (sqrt(pow((minEllipse[i].center.x - limiteX),2)+pow((minEllipse[i].center.y - limiteY),2)) > rayon10))
                {
                    cout << "coup " << coupsTotal << " : " << " 9 " << endl;
                    scoreTotal += 9;
                    valeurCoup = 9;
                }
                else
                {
                    cout << "coup " << coupsTotal << " : " << " 10 " << endl;
                    scoreTotal += 10;
                    valeurCoup = 10;
                }
                
                
                //On dessine les impacts trouvés sur notre cible.
                circle(img, minEllipse[i].center, (4.5*coefficient), Scalar(0, 0, 255),-1);
                
                //On ecrit les scores dans la fenètre
                string var;
                var += "coup ";
                var += to_string(coupsTotal);
                var += " : ";
                var += to_string(valeurCoup);
                
                marginTop += 20;
                putText(pic,var,Point(50,marginTop), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255),1,8,false);
                
            }
            
        }
    }
    
    
    /// Show in a window
    namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
    
    namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
    namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
    
    moveWindow("MyWindow", 0, 0);
    moveWindow("Original Image", 620, 0);
    
    //on affiche 'img' in the "MyWindow" window
    imshow("MyWindow", img2);
    imshow("Original Image", img);
    
    
    //Affichage des scores
    cout << "Nombres de coups trouvés : " << coupsTotal << endl;
    cout << "Score total : " << scoreTotal << " / " << coupsTotal*10 << endl;
    
    //Creation d'une fenetre pour afficher du texte
    string text;
    text = "Nombre de coups trouves : ";
    text += to_string(coupsTotal);
    putText(pic,text,cv::Point(50,marginTop+20), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255),1,8,false);
    
    text = "Resultat Total : ";
    text += to_string(scoreTotal);
    text += " / ";
    text += to_string(coupsTotal*10);
    putText(pic,text,cv::Point(50,marginTop+40), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255),1,8,false);
    
    
    //On affiche la fenêtre avec nos résultats
    namedWindow( "Results", CV_WINDOW_AUTOSIZE );
    imshow( "Results", pic );
    
    //attente input clavier
    waitKey(0);
    
    // libère "MyWindow"
    destroyWindow("MyWindow");
}

int main( int argc, const char** argv ) {
    
    openImg();
    
    return 0;
}

