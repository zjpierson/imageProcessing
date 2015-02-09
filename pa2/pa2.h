/*
               ***** pa2.h *****

Demo program to illustrate qtImageLib.
Example 2 shows how to add menu items to the default image viewer.

Author: John M. Weiss, Ph.D.
Written Spring 2015 for SDSM&T CSC442/542 DIP course.

Modifications:
*/

// next two lines are typical
#pragma once
#include <qtimagelib.h>

// class declaration
class MyApp : public QObject
{
    Q_OBJECT;	// QOBJECT macro must appear at start of class

    // all menu items must be prototyped in the "public slots" section
    // note the method prototype and naming conventions:
    // bool Menu_Menubar_Menuitem( Image & );

  public slots:

    bool Menu_Palette_Threshold( Image & );
    bool Menu_Palette_Embossing( Image & );
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
    bool Menu_Filter_Gaussian( Image & );

    bool Menu_Edge_SobelMagnitude( Image & );
    bool Menu_Edge_SobelDirection( Image & );
    bool Menu_Edge_KirschMagnitude( Image & );
    bool Menu_Edge_KirschDirection( Image & );
    bool Menu_Edge_Laplacian( Image & );


};
