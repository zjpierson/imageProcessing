/*
               ***** example4.cpp *****

Demo program to illustrate qtImageLib.
Example 3 shows how to add user-defined functionality (as well as QtImageLib routines) to an application,
and get user input via dialog boxes.
Grayscaling and smoothing are implemented in separate files.

Author: John M. Weiss, Ph.D.
Written Spring 2015 for SDSM&T CSC442/542 DIP course.

Modifications:
*/

// QtImageLib requires interface (example4.h) as well as implementation (example4.cpp)
#include "example4.h"

// typical main function
int main( int argc, char *argv[] )
{
    MyApp obj;
    ImageApp app( argc, argv );
    app.AddActions( &obj );
    return app.Start();
}

// ----------------------------------- menu bar additions ------------------------------------

// the following methods add actions to the menu bar
// note the method prototype and naming conventions:
// bool ClassName::Menu_Menubar_Menuitem( Image & );

// ----------------------------------- palette manipulations ---------------------------------

// negate the image
bool MyApp::Menu_Palette_Negate( Image &image )
{
    negatePalette( image );
    return true;
}

// convert a color image to grayscale
bool MyApp::Menu_Palette_Grayscale( Image &image )
{
    grayscale( image );
    return true;
}

// adjust image brightness (note use of Dialog)
bool MyApp::Menu_Palette_Brightness( Image &image )
{
    int c = 0;
    if ( !Dialog( "Brightness" ).Add( c, "offset", -255, 255 ).Show() )
        return false;
    imageAddConstant( image, c );
    return true;
}

// ----------------------------------- histogram routines ------------------------------------

// display histogram
bool MyApp::Menu_Histogram_Display( Image &image )
{
    displayHistogram( image );
    return true;
}

// histogram contrast stretch
bool MyApp::Menu_Histogram_Stretch( Image &image )
{
    histogramStretch( image );
    return true;
}

// histogram contrast stretch with specified endpoints (note use of Dialog)
bool MyApp::Menu_Histogram_StretchSpecify( Image &image )
{
    double left = 1.0, right = 1.0;
    if ( !Dialog( "endpoints" ).Add( left, "left", 0.0, 100.0 ).Add( right, "right", 0.0, 100.0 ).Show() )
        return false;
    histogramStretchSpecify( image, left, right);
    return true;
}

// ----------------------------------- spatial filtering -------------------------------------

// smooth the image (3x3 center-weighted smoothing filter)
bool MyApp::Menu_Filter_Smooth( Image &image )
{
    smooth( image );
    return true;
}

// Gaussian smoothing filter (note use of getParams)
bool MyApp::Menu_Filter_GaussianSmooth( Image &image )
{
    double sigma = 2.0;
    if ( !getParams( sigma ) ) return false;
    smoothGaussian( image, sigma );
    return true;
}

// sharpen the image
bool MyApp::Menu_Filter_Sharpen( Image &image )
{
    sharpen( image );
    return true;
}

// ----------------------------------- edge detection ----------------------------------------

// Sobel edge detection
bool MyApp::Menu_Edge_Sobel( Image &image )
{
    sobel( image );
    return true;
}

// Sobel edge detection
bool MyApp::Menu_Edge_SobelMagnitude( Image &image )
{
    sobelMagnitude( image );
    return true;
}

// Sobel edge detection
bool MyApp::Menu_Edge_SobelDirection( Image &image )
{
    sobelDirection( image );
    return true;
}
