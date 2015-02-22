#include "pa2.h"

bool MyApp::Menu_Edge_SobelMagnitude( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice

    int nrows = image.Height();
    int ncols = image.Width();

    Image Gy(image);
    Image Gx(image);

    sobel_x(Gx);
    sobel_y(Gy);

    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
        {
            image[r][c] = sqrt( (Gx[r][c]*Gx[r][c]) + (Gy[r][c]*Gy[r][c]) );
        }
    }
    
    return true;
}


bool MyApp::sobel_x( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int row = 0;
    int col = 0;
    int i = 0;
    int sum = 0;
    int rbound = 0;
    int cbound = 0;

    //create filter mask matrix
    //These are seperable, but using a 3x3 matrix
    int matrixArr[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

    //make copy of image as to not destroy original information
    Image temp(image);
    
    for ( int r = 1; r < nrows - 1; r++ )
    {
        for ( int c = 1; c < ncols - 1; c++ )
        {
            //neighborhood boundries
            rbound = r - 1;
            cbound = c - 1;
            
            //begins the loop through inner filter
            for(row = r-1; row < (3+rbound); row++)
            {
                for(col = c-1; col < (3+cbound); col++)
                {
                    sum += matrixArr[i] * temp[row][col];
                    i++;
                }
            }
            
            //make sure values are in range
            sum = abs(sum);
            if(sum > 255)
                image[r][c] = 255;
            else
                image[r][c] = sum;

            //reset neighborhood variables
            i = 0;
            sum = 0;
        }
    }

    // return true to update the image
    return true;
}

bool MyApp::sobel_y( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int row = 0;
    int col = 0;
    int i = 0;
    int sum = 0;
    int rbound = 0;
    int cbound = 0;

    //create filter mask matrix
    //These are seperable, but using a 3x3 matrix
    int matrixArr[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};

    //make copy of image as to not destroy original information
    Image temp(image);
    
    for ( int r = 1; r < nrows - 1; r++ )
    {
        for ( int c = 1; c < ncols - 1; c++ )
        {
            //neighborhood boundries
            rbound = r - 1;
            cbound = c - 1;
            
            //begins the loop through inner filter
            for(row = r-1; row < (3+rbound); row++)
            {
                for(col = c-1; col < (3+cbound); col++)
                {
                    sum += matrixArr[i] * temp[row][col];
                    i++;
                }
            }
            
            //make sure values are in range
            sum = abs(sum);
            if(sum > 255)
                image[r][c] = 255;
            else
                image[r][c] = sum;

            //reset neighborhood variables
            i = 0;
            sum = 0;
        }
    }


    // return true to update the image
    return true;
}


bool MyApp::Menu_Edge_SobelDirection( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice

    int nrows = image.Height();
    int ncols = image.Width();
    double value = 0;

    Image Gx(image);
    Image Gy(image);

    sobel_x(Gx);
    sobel_y(Gy);

    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
        {
            //calculates arc tan
            value = atan2((double)Gy[r][c], (double)Gx[r][c]); 

            //changes negative values to positive radians
            if(value < 0)
                value = (value + (2*M_PI));

            //scales the range from 0-2pi to 0-255
            image[r][c] = ( (2*M_PI)/value );
//            image[r][c] = ((255.0/value) * (2*M_PI));
        }
    }
    
    // return true to update the image
    return true;
}

bool MyApp::Menu_Edge_KirschMagnitude( Image &image )
{
    return true;
}

bool MyApp::Menu_Edge_KirschDirection( Image &image )
{
    return true;
}

bool MyApp::Menu_Edge_Laplacian( Image &image )
{
    return true;
}
