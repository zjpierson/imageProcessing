/*
               ***** example2.cpp *****

Demo program to illustrate qtImageLib.
Example 2 shows how to add menu items to the default image viewer.

Author: John M. Weiss, Ph.D.
Written Spring 2015 for SDSM&T CSC442/542 DIP course.

Modifications:
*/

// QtImageLib requires interface (example2.h) as well as implementation (example2.cpp)
#include "example2.h"

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
