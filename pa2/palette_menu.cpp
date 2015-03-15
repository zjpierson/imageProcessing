/************************************************************************
* Program: Neighborhood Processing - Assignment 2 
* Author: Kayhan Karatekeli & Zachary Pierson
* Class: CSC 442 - Digital Image Processing
* Instructor: Dr. John Weiss
* Date: 2/26/15
* Description: This program is designed to apply spacial-domain filters
*              and neighborhood operators to an image.
*
* File: The file contains the palette options in the palette menu.
************************************************************************/

#include "pa2.h"

/************************************************************************
Function:     Display
Description:  This function sets a binary threshold for an image using
              the built in QT function.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Palette_Threshold( Image &image )
{
    int thresh = 128;
    if ( !Dialog( "grayscale threshold" ).Add( thresh, "Threshold", 1, 255 ).Show() )
        return false;
    binaryThreshold( image, thresh );
    return true;
}

/************************************************************************
Function:     Display
Description:  This function sets the image to a greyscale image using
              the built in QT function.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Palette_Grayscale( Image &image )
{
    grayscale( image );
    return true;
}
