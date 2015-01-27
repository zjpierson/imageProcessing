/*
               ***** pa1.h *****

Demo program to illustrate qtImageLib.
Example 2 shows how to add menu items to the default image viewer.

Author: John M. Weiss, Ph.D.
Written Spring 2015 for SDSM&T CSC442/542 DIP course.

Modifications:
*/

// next two lines are typical
#pragma once
#include <qtimagelib.h>
#include <time.h>
#include <iostream>
#include <math.h>

// class declaration
class MyApp : public QObject
{
    Q_OBJECT;	// QOBJECT macro must appear at start of class
    static unsigned char LUTgrayscale[256][256][256];
    static unsigned char LUTnegate[256];

    bool grayscaleINIT;
    bool negateINIT;

    void init_LUTgrayscale();
    void init_LUTnegate();

    // all menu items must be prototyped in the "public slots" section
    // note the method prototype and naming conventions:
    // bool Menu_Menubar_Menuitem( Image & );
    public:
        MyApp();

    public slots:

        bool Menu_Palette_Grayscale( Image & );
        bool Menu_Palette_Negate( Image & );
        bool Menu_Palette_Threshold( Image & );
        bool Menu_Palette_Posterize( Image & );
        bool Menu_Palette_Brightness( Image & );
        bool Menu_Palette_Contrast( Image & );
        bool Menu_Palette_Gamma( Image & );
        bool Menu_Palette_Log( Image & );
       
        bool Menu_Histogram_Display( Image & );
        bool Menu_Histogram_AutoStretch( Image & );
        bool Menu_Histogram_ModStretch( Image & );
        bool Menu_Histogram_Equalize( Image & );
        bool Menu_Histogram_ClipEqualize( Image & );

        bool Menu_Color_DiscretePseudocolor( Image & );
        bool Menu_Color_ContinuousPseudocolor( Image & );
};
