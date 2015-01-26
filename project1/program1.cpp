/*
               ***** example2.cpp *****

Demo program to illustrate qtImageLib.
Example 2 shows how to add menu items to the default image viewer.

Author: John M. Weiss, Ph.D.
Written Spring 2015 for SDSM&T CSC442/542 DIP course.

Modifications:
*/

// QtImageLib requires interface (example2.h) as well as implementation (example2.cpp)
#include "program1.h"
#include <iostream>
using namespace std;

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
//bool MyApp::Menu_Palette_MyGrayscale( Image &image )
bool MyApp::Menu_Palette_Grayscale( Image &image )
{
    if ( image.IsNull() ) return false; // not essential, but good practice

    static unsigned char LUTgrayscale[256][256][256];

    //Compute Look Up Table for grayscale
    for ( int r = 0; r < 256; r++)
        for ( int g = 0; g < 256; g++)
            for ( int b = 0; b < 256; b++)
                LUTgrayscale[r][g][b] = ( .3*r + .59*g + .11*b);

    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
        for ( int c = 0; c < ncols; c++ )
        {
            // red/green/blue channels can be accessed directly using
            // image[r][c].rgb.x (where x is r/g/b), but this is not recommended
            unsigned char red = image[r][c].Red();
            unsigned char green = image[r][c].Green();
            unsigned char blue = image[r][c].Blue();

            int gray = LUTgrayscale[red][green][blue];

            image[r][c].SetGray( gray );
        }

    // return true to update the image
    return true;
}

bool MyApp::Menu_Palette_Negate( Image &image )
{
    return true;
}

bool MyApp::Menu_Palette_Threshold( Image &image )
{
    return true;
}

bool MyApp::Menu_Palette_Posterize( Image &image )
{
    return true;
}

bool MyApp::Menu_Palette_Brightness( Image &image )
{
    return true;
}

bool MyApp::Menu_Palette_Contrast( Image &image )
{
    return true;
}

bool MyApp::Menu_Palette_Gamma( Image &image )
{
    return true;
}

bool MyApp::Menu_Palette_Log( Image &image )
{
    return true;
}

bool MyApp::Menu_Histogram_Display( Image &image )
{
    return true;
}

bool MyApp::Menu_Histogram_AutoStretch( Image &image )
{
    return true;
}

bool MyApp::Menu_Histogram_ModStretch( Image &image )
{
    return true;
}

bool MyApp::Menu_Histogram_Equalize( Image &image )
{
    return true;
}

bool MyApp::Menu_Histogram_ClipEqualize( Image &image )
{
    return true;
}

bool MyApp::Menu_Color_DiscretePseudocolor( Image &image )
{
    return true;
}

bool MyApp::Menu_Color_ContinuousPseudocolor( Image &image )
{
    return true;
}


// ---------------------------------------------------------------------------------------

//
//// negate the image
//bool MyApp::Menu_Palette_Negate( Image &image )
//{
//    negatePalette( image );
//    return true;
//}
//
//// convert a color image to grayscale
//bool MyApp::Menu_Palette_Grayscale( Image &image )
//{
//    grayscale( image );
//    return true;
//}
//
//// display histogram
//bool MyApp::Menu_Histogram_Display( Image &image )
//{
//    displayHistogram( image );
//    return true;
//}
//
//// histogram contrast stretch
//bool MyApp::Menu_Histogram_Stretch( Image &image )
//{
//    histogramStretch( image );
//    return true;
//}

//bool MyApp::Menu_Palette_MyGrayscale( Image &image )
//{
//    if ( image.IsNull() ) return false; // not essential, but good practice
//
//    // convert RGB values to HSI intensities
//    int nrows = image.Height();
//    int ncols = image.Width();
//    for ( int r = 0; r < nrows; r++ )
//        for ( int c = 0; c < ncols; c++ )
//        {
//            // red/green/blue channels can be accessed directly using
//            // image[r][c].rgb.x (where x is r/g/b), but this is not recommended
//            int red = image[r][c].Red();
//            int green = image[r][c].Green();
//            int blue = image[r][c].Blue();
//
//            // HSI intensity component is defined as ( R + G + B ) / 3
//            int gray = ( red + green + blue ) / 3.0 + 0.5;
//            image[r][c].SetRed( gray );
//            image[r][c].SetGreen( gray );
//            image[r][c].SetBlue( gray );
//            // or, image[r][c].SetRGB( gray, gray, gray );
//            // or, image[r][c].SetGray( gray ) to set all three at once
//        }
//
//    // return true to update the image
//    return true;
//}
