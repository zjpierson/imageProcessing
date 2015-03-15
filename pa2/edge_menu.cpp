/************************************************************************
* Program: Neighborhood Processing - Assignment 2 
* Author: Kayhan Karatekeli & Zachary Pierson
* Class: CSC 442 - Digital Image Processing
* Instructor: Dr. John Weiss
* Date: 2/26/15
* Description: This program is designed to apply spacial-domain filters
*              and neighborhood operators to an image.
*
* File: This file contains the edge operators supplied in the edge menu.
************************************************************************/

#include "pa2.h"

/************************************************************************
Function:     SobelMagnitude
Description:  This function calculates the Sobel edge magnitude. 
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
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


/************************************************************************
Function:     sobel_x
Description:  This function calculates the Sobel edge mask on the X
              coordinates. This is used withing the SobelMagnitude. 
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
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

/************************************************************************
Function:     sobel_y
Description:  This function calculates the Sobel edge mask on the Y
              coordinates. This is used withing the SobelMagnitude. 
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
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

/************************************************************************
Function:     SobelDirection
Description:  This function calculates the Sobel edge mask on the X & Y
              coordinates. They are then utilized to calculate the arctan
              of the intensities, which is then scaled from 0-255. 
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Edge_SobelDirection( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int row = 0;
    int col = 0;
    int i = 0;
    int sumX = 0;
    int sumY = 0;
    int rbound = 0;
    int cbound = 0;
    double value = 0;

    //create filter mask matrix
    //These are seperable, but using a 3x3 matrix
    int maskX[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int maskY[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

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
                    sumX += maskX[i] * temp[row][col];
                    sumY += maskY[i] * temp[row][col];
                    i++;
                }
            }

            value = atan2((double)sumY, (double)sumX); 

            //changes negative values to positive radians
            if(value < 0)
                value = (value + (2*M_PI));

            //scales the range from 0-2pi to 0-255
            image[r][c] = ((value/(2*M_PI)) * 255.0);

            //reset neighborhood variables
            i = 0;
            sumX = 0;
            sumY = 0;
        }
    }
    
    // return true to update the image
    return true;
}

/************************************************************************
Function:     KirschMagnitude
Description:  This function calculates the Kirsch edge magnitude of the
              imagei using 8 rotations. 
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Edge_KirschMagnitude( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int row = 0;
    int col = 0;
    int i = 0;
    double value = 0;
    int max = -1;

    //create filter mask matrix
    //create an array of masks
    int rotation[8][9]={-3, -3, -3, -3, 0, -3, 5, 5, 5,
                        -3, -3, -3, 5, 0, -3, 5, 5, -3,
                        5, -3, -3, 5, 0, -3, 5, -3, -3,
                        5, 5, -3, 5, 0, -3, -3, -3, -3,
                        5, 5, 5, -3, 0, -3, -3, -3, -3,
                        -3, 5, 5, -3, 0, 5, -3, -3, -3,
                        -3, -3, 5, -3, 0, 5, -3, -3, 5,
                        -3, -3, -3, -3, 0, 5, -3, 5, 5};
    int rotationSum[8] = {0};

    //make copy of image as to not destroy original information
    Image temp(image);
    
    for ( int r = 1; r < nrows - 1; r++ )
    {
        for ( int c = 1; c < ncols - 1; c++ )
        {
            //begins the loop through inner filter
            for(row = r-1; row <= r+1; row++)
            {
                for(col = c-1; col <= c+1; col++)
                {
                    for(int j = 0; j < 8; j++)
                        rotationSum[j] += rotation[j][i] * temp[row][col];
                    i++;
                }
            }
            
            //set image to maximum sum of rotation 
            //masks divided by 3 and clipped
            maxKirsch(rotationSum, max);

            value = ((double)max/3.0);

            if(value > 255)
                value = 255;

            image[r][c] = value;

            //reset neighborhood variables and the sum's
            i = 0;
        }
    }
    
    // return true to update the image
    return true;
}

/************************************************************************
Function:     maxKirsch
Description:  This function calculates the maximum of the 8 rotations.
Parameters:   param[in]  rotationSum - Array of sums for each mask.
              param[in]  max         - Maximum value of all masks. 
              param[out] index - The specific rotation matrix used.
************************************************************************/
int MyApp::maxKirsch(int rotationSum[], int & max)
{
    max = -1;
    int index;

    for(int i = 0; i < 8; i++)
    {
        if(rotationSum[i] > max)
        {
            index = i;
            max = rotationSum[i];
        }

        //reset rotation back to 0 for next pass
        rotationSum[i] = 0;
    }

    return index;
}

/************************************************************************
Function:     KirschDirection
Description:  Calculates the Kirsch edge using the direction coordinates
              +/- 22.5 degrees.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Edge_KirschDirection( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int row = 0;
    int col = 0;
    int i = 0;
    int max = -1;
    int index = 0;

    //create filter mask matrix
    //create an array of masks
    int rotation[8][9]={-3, -3, 5, -3, 0, 5, -3, -3, 5,
                        -3, 5, 5, -3, 0, 5, -3, -3, -3,
                        5, 5, 5, -3, 0, -3, -3, -3, -3,
                        5, 5, -3, 5, 0, -3, -3, -3, -3,
                        5, -3, -3, 5, 0, -3, 5, -3, -3,
                        -3, -3, -3, 5, 0, -3, 5, 5, -3,
                        -3, -3, -3, -3, 0, -3, 5, 5, 5, 
                        -3, -3, -3, -3, 0, 5, -3, 5, 5};
    int rotationSum[8] = {0};

    //make copy of image as to not destroy original information
    Image temp(image);
    
    for ( int r = 1; r < nrows - 1; r++ )
    {
        for ( int c = 1; c < ncols - 1; c++ )
        {
            //begins the loop through inner filter
            for(row = r-1; row <= r+1; row++)
            {
                for(col = c-1; col <= c+1; col++)
                {
                    for(int j = 0; j < 8; j++)
                        rotationSum[j] += rotation[j][i] * temp[row][col];
                    i++;
                }
            }
            
            //set image to angle of maximum rotation 
            index = maxKirsch(rotationSum, max);

            image[r][c] = ((double)(index * 45)/360.0) * 255;

            //reset neighborhood variable
            i = 0;
        }
    }
    
    // return true to update the image
    return true;
}

/************************************************************************
Function:     Lapalcian
Description:  This fucntion is designed to calculate the Laplacian
              edges of the image.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Edge_Laplacian( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int row = 0;
    int col = 0;
    int i = 0;
    int sum = 128;

    //create filter mask matrix
    //These are seperable, but using a 3x3 matrix
    int matrix[9] = {0, -1, 0, -1, 4, -1, 0, -1, 0};

    //make copy of image as to not destroy original information
    Image temp(image);
    
    for ( int r = 1; r < nrows - 1; r++ )
    {
        for ( int c = 1; c < ncols - 1; c++ )
        {
            //begins the loop through inner filter
            for(row = r-1; row <= r+1; row++)
            {
                for(col = c-1; col <= c+1; col++)
                {
                    sum += matrix[i] * temp[row][col];
                    i++;
                }
            }

            //check if out of range
            if(sum < 0)
                image[r][c] = 0;
            else if(sum > 255)
                image[r][c] = 255;
            else
                image[r][c] = sum;

            //resets variables
            i = 0;
            sum = 128;
        }
    }
    
    // return true to update the image
    return true;
}
