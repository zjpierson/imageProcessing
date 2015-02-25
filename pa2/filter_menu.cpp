/************************************************************************
* Program: Neighborhood Processing - Assignment 2 
* Author: Kayhan Karatekeli & Zachary Pierson
* Class: CSC 442 - Digital Image Processing
* Instructor: Dr. John Weiss
* Date: 2/26/15
* Description: This program is designed to apply spacial-domain filters
*              and neighborhood operators to an image.
*
* File: The file contains the filtering options in the filter menu.
************************************************************************/
#include "pa2.h"

/************************************************************************
Function:     Smoothing
Description:  This function smooths the image.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Filter_Smoothing_3x3( Image &image )
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
    int matrixArr[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1};

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
                    sum += matrixArr[i] * image[row][col];
                    i++;
                }
            }
            
            //set the resulting pixel to a temporary image
            temp[r][c] = (sum/16);

            //reset neighborhood variables
            i = 0;
            sum = 0;
        }
    }

    image = temp;

    // return true to update the image
    return true;
}

/************************************************************************
Function:     Sharpening
Description:  This function sharpens the image.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Filter_Sharpening_3x3( Image &image )
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
    int matrixArr[9] = {0, -1, 0, -1, 5, -1, 0, -1, 0};

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
                    sum += matrixArr[i] * image[row][col];
                    i++;
                }
            }
            
            //set the resulting pixel to a temporary image
            if(sum < 0)
                temp[r][c] = 0;
            else if(sum > 255)
                temp[r][c] = 255;
            else
                temp[r][c] = sum;

            //reset neighborhood variables
            i = 0;
            sum = 0;
        }
    }

    image = temp;

    // return true to update the image
    return true;
}

/************************************************************************
Function:     PlusMedian
Description:  This function takes the median values of a neighborhood
              using a mask in the shape of a plus.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Filter_PlusMedian( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int row = 0;
    int col = 0;
    int i = 0;
    int j = 0;
    int rbound = 0;
    int cbound = 0;

    //create filter mask matrix
    int matrixA[9] = {0, 1, 0, 1, 1, 1, 0, 1, 0};
    int med[5] = {0};

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
                    if(matrixA[i] == 1)
                    {
                        med[j] = image[row][col];
                        j++;
                    }
                    i++;
                }
            }
            
            //find median and set temp image[r][c] to that pixel
            temp[r][c] = median(med, 5);

            //reset neighborhood variables
            i = 0;
            j = 0;
        }
    }

    image = temp;

    // return true to update the image
    return true;
}

int MyApp::median(int array[], int size)
{
    int j = 0;
    int temp = 0;

    for(int i = 1; i < size; i++)
    {
        j = i;

        while(j > 0 && array[j-1] > array[j])    
        {
            temp = array[j];
            array[j] = array[j-1];
            array[j-1] = temp;
            j--;
        }
    }

    return array[size/2];
}

/************************************************************************
Function:     NoiseCleaning
Description:  This function cleans noise in the image using an ad-hoc
              technique.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Filter_NoiseCleaning( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    int threshold = 32;
    if( !Dialog("Threshold").Add(threshold, "set", 0, 255).Show())
            return false;

    int avg = 0;

    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int row = 0;
    int col = 0;
    int rbound = 0;
    int cbound = 0;

    //make copy of image as to not destroy original information
    Image temp(image);
    
    for ( int r = 1; r < nrows - 1; r++ )
    {
        for ( int c = 1; c < ncols - 1; c++ )
        {
            //neighborhood boundries
            rbound = r - 1;
            cbound = c - 1;
            
            //begins the loop through inner filter (neighborhood)
            for(row = r-1; row < (3+rbound); row++)
            {
                for(col = c-1; col < (3+cbound); col++)
                {
                    //add up all the pixels except for the center pixel
                    if( row == r && col == c )
                        continue;
                    avg += image[row][col];
                }
            }
            
            //compute avg (devide sum by 8)
            avg /= 8;

            //do thresholding 
            if( abs(image[r][c] - avg) > threshold )
                temp[r][c] = avg;

            //reset loop variables
            avg = 0;
        }
    }

    image = temp;

    // return true to update the image
    return true;
}

/************************************************************************
Function:     Mean
Description:  This function takes the median values of a neighborhood.
              The function uses SEPREABILITY to perform its operation.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Filter_Mean( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int n = 15;
    int border = 0;
    int sum = 0;

    if(! getParams(n))  return false;

    if( n % 2 == 0 )
        n++;

    //making use of int division
    border = (n/2);

    //make copy of image as to not destroy original information
    Image temp(image);

    //first pass going through the rows
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = border; c < (ncols - border); c++ )
        {
            //loop though neighborhood
            for(int i = (c - border); i < (c + border); i++)
            {
                sum += image[r][i];
            }
            temp[r][c] = (sum/n);
            sum = 0;
        }
    }

    //second pass going through the columns
    for ( int c = 0; c < ncols; c++ )
    {
        for ( int r = border; r < (nrows - border); r++ )
        {
            //loop though neighborhood
            for(int i = (r - border); i < (r + border); i++)
            {
                sum += temp[i][c];
            }
            image[r][c] = (sum/n);
            sum = 0;
        }
    }

    // return true to update the image
    return true;
}

/************************************************************************
Function:     Median
Description:  This function takes the median values of a neighborhood.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Filter_Median( Image &image )
{
    return true;
}

/************************************************************************
Function:     Minimun
Description:  This function takes the minimum values of a neighborhood.
              The function uses SEPREABILITY to perform its operation.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Filter_Minimum( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int n = 15;
    int border = 0;
    int sum = 0;
    int min = 256;
    

    if(! getParams(n))  return false;

    if( n % 2 == 0 )
        n++;

    //making use of int division
    border = (n/2);

    //make copy of image as to not destroy original information
    Image temp(image);

    //first pass going through the rows
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = border; c < (ncols - border); c++ )
        {
            //loop though neighborhood
            for(int i = (c - border); i < (c + border); i++)
            {
                if(image[r][i] < min)
                    min = image[r][i];
            }
            temp[r][c] = min;
            min = 256;
        }
    }

    //second pass going through the columns
    for ( int c = 0; c < ncols; c++ )
    {
        for ( int r = border; r < (nrows - border); r++ )
        {
            //loop though neighborhood
            for(int i = (r - border); i < (r + border); i++)
            {
                if(temp[i][c] < min)
                    min = temp[i][c];
            }
            image[r][c] = min;
            min = 256;
        }
    }

    // return true to update the image
    return true;
}

/************************************************************************
Function:     Maximum
Description:  This function takes the maximum values of a neighborhood.
              The function uses SEPREABILITY to perform its operation.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Filter_Maximum( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int n = 15;
    int border = 0;
    int sum = 0;
    int max = 0;
    

    if(! getParams(n))  return false;

    if( n % 2 == 0 )
        n++;

    //making use of int division
    border = (n/2);

    //make copy of image as to not destroy original information
    Image temp(image);

    //first pass going through the rows
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = border; c < (ncols - border); c++ )
        {
            //loop though neighborhood
            for(int i = (c - border); i < (c + border); i++)
            {
                if(image[r][i] > max)
                    max = image[r][i];
            }
            temp[r][c] = max;
            max = 0;
        }
    }

    //second pass going through the columns
    for ( int c = 0; c < ncols; c++ )
    {
        for ( int r = border; r < (nrows - border); r++ )
        {
            //loop though neighborhood
            for(int i = (r - border); i < (r + border); i++)
            {
                if(temp[i][c] > max)
                    max = temp[i][c];
            }
            image[r][c] = max;
            max = 0;
        }
    }

    // return true to update the image
    return true;
}

/************************************************************************
Function:     Range
Description:  This function takes the range of values of a neighborhood.
              The function uses SEPREABILITY to perform its operation.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Filter_Range( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int n = 15;
    int border = 0;
    int sum = 0;
    int max = 0;
    int min = 256;
    

    if(! getParams(n))  return false;

    if( n % 2 == 0 )
        n++;

    //making use of int division
    border = (n/2);

    //make copy of image as to not destroy original information
    Image temp(image);

    //first pass going through the rows
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = border; c < (ncols - border); c++ )
        {
            //loop though neighborhood
            for(int i = (c - border); i < (c + border); i++)
            {
                if(image[r][i] > max)
                    max = image[r][i];
                if(image[r][i] < min)
                    min = image[r][i];
            }
            temp[r][c] = max - min;
            max = 0;
            min = 256;
        }
    }

    //second pass going through the columns
    for ( int c = 0; c < ncols; c++ )
    {
        for ( int r = border; r < (nrows - border); r++ )
        {
            //loop though neighborhood
            for(int i = (r - border); i < (r + border); i++)
            {
                if(temp[i][c] > max)
                    max = temp[i][c];
                if(temp[i][c] < min)
                    min = temp[i][c];
            }
            image[r][c] = max - min;
            max = 0;
            min = 256;
        }
    }

    // return true to update the image
    return true;
}

/************************************************************************
Function:     StandardDeviation
Description:  This function takes the standard deviation of values of 
              a neighborhood.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Filter_StandardDeviation( Image &image )
{
    return true;
}

/************************************************************************
Function:     Emboss
Description:  This function creates an embossing technique on the image. 
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Filter_Emboss(Image &image )
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
    int matrixArr[9] = {0, 0, 0, 0, 1, 0, 0, 0, -1};

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
                    sum += matrixArr[i] * image[row][col];
                    i++;
                }
            }
            
            temp[r][c] = (sum + 255)/2;

            //reset neighborhood variables
            i = 0;
            sum = 0;
        }
    }

    image = temp;

    // return true to update the image
    return true;
}

/************************************************************************
Function:     Gaussian
Description:  This function preforms a Gaussian smoothing on the image. 
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Filter_Gaussian( Image &image )
{
    return true;
}

