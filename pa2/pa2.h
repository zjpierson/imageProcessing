/************************************************************************
* Program: Neighborhood Processing - Assignment 2 
* Author: Kayhan Karatekeli & Zachary Pierson
* Class: CSC 442 - Digital Image Processing
* Instructor: Dr. John Weiss
* Date: 2/26/15
* Description: This program is designed to apply spacial-domain filters
*              and neighborhood operators to an image.
*
* File: This file holds the function prototypes for the program. 
************************************************************************/

#pragma once
#include <qtimagelib.h>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <vector>

using namespace std;

// class declaration
class MyApp : public QObject
{
    Q_OBJECT;	// QOBJECT macro must appear at start of class

  public:
    int median(int array[], int size);
    int median(vector<int> array);
    bool sobel_y( Image &image );
    bool sobel_x( Image &image );
    int maxKirsch(int rotationSum[], int & max);

  public slots:
    bool Menu_Palette_Threshold( Image & );
    bool Menu_Palette_Grayscale( Image & );

    bool Menu_Histogram_Display( Image & );
    bool Menu_Histogram_Stretch( Image & );
    bool Menu_Histogram_Equalize( Image & );

    bool Menu_Noise_Gaussian( Image & );
    bool Menu_Noise_Impulse( Image & );

    bool Menu_Filter_Smoothing_3x3( Image & );
    bool Menu_Filter_Sharpening_3x3( Image & );
    bool Menu_Filter_PlusMedian( Image & );
    bool Menu_Filter_NoiseCleaning( Image & );
    bool Menu_Filter_Mean( Image & );
    bool Menu_Filter_Median( Image & );
    bool Menu_Filter_Minimum( Image & );
    bool Menu_Filter_Maximum( Image & );
    bool Menu_Filter_Range( Image & );
    bool Menu_Filter_StandardDeviation( Image & );
    bool Menu_Filter_Emboss(Image & );

    bool Menu_Edge_SobelMagnitude( Image & );
    bool Menu_Edge_SobelDirection( Image & );
    bool Menu_Edge_KirschMagnitude( Image & );
    bool Menu_Edge_KirschDirection( Image & );
    bool Menu_Edge_Laplacian( Image & );
};
