/*
               ***** smooth.cpp *****

3x3 image smoothing in the spatial domain.

Author: John M. Weiss, Ph.D.
Written Spring 2015 for SDSM&T CSC442/542 DIP course.

Modifications:
*/

#include "example4.h"

bool MyApp::Menu_Filter_MySmooth( Image &image )
{
    if ( image.IsNull() ) return false; // not essential, but good practice

    // make image copy (to avoid recursive calculations)
    int nrows = image.Height();
    int ncols = image.Width();
    Image copy = image;
    
    // smooth image by 3x3 averaging
    for ( int r = 1; r < nrows - 1; r++ )
    {
        for ( int c = 1; c < ncols - 1; c++ )
        {
            // sum 3x3 neighborhood about current pixel
            int sum = 0;
            for ( int i = -1; i <= 1; i++ )
                for ( int j = -1; j <= 1; j++ )
                    sum +=  copy[r + i][c + j];

            // store result
            image[r][c] = sum / 9.0 + 0.5;
        }
    }

    // update image and return
    return true;
}
