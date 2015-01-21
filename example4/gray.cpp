/*
               ***** gray.cpp *****

Routine to convert an image from color to grayscale.

Author: John M. Weiss, Ph.D.
Written Spring 2015 for SDSM&T CSC442/542 DIP course.

Modifications:
*/

#include "example4.h"

// convert a color image to grayscale
bool MyApp::Menu_Palette_MyGrayscale( Image &image )
{
    if ( image.IsNull() ) return false; // not essential, but good practice

    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
        for ( int c = 0; c < ncols; c++ )
        {
            // red/green/blue channels can be accessed directly using
            // image[r][c].rgb.x (where x is r/g/b), but this is not recommended
            int red = image[r][c].Red();
            int green = image[r][c].Green();
            int blue = image[r][c].Blue();

            // HSI intensity component is defined as ( R + G + B ) / 3
            int gray = ( red + green + blue ) / 3.0 + 0.5;
            image[r][c].SetRed( gray );
            image[r][c].SetGreen( gray );
            image[r][c].SetBlue( gray );
            // or, image[r][c].SetRGB( gray, gray, gray );
            // or, image[r][c].SetGray( gray ) to set all three at once
        }

    // return true to update the image
    return true;
}
