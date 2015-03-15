/************************************************************************
* Program: Neighborhood Processing - Assignment 2 
* Author: Kayhan Karatekeli & Zachary Pierson
* Class: CSC 442 - Digital Image Processing
* Instructor: Dr. John Weiss
* Date: 2/26/15
* Description: This program is designed to apply spacial-domain filters
*              and neighborhood operators to an image.
*
* File: The file contains the histogram options in the histogram menu.
************************************************************************/

#include "pa2.h"

/************************************************************************
Function:     Display
Description:  This function displays an image using the built in
              QT function.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Histogram_Display( Image &image )
{
    displayHistogram( image );
    return true;
}

/************************************************************************
Function:     Stretch
Description:  This function performs a histogram stretch on an image
              using the built in QT function.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Histogram_Stretch( Image &image )
{
    histogramStretch( image );
    return true;
}

/************************************************************************
Function:     Equalize
Description:  This function performs a histogram equalize on an image
              followed by a stretch using the built in QT function.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Histogram_Equalize( Image &image )
{
    histogramEqualize( image );
    histogramStretch( image );
    return true;
}
