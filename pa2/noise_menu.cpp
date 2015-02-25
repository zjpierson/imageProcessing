/************************************************************************
* Program: Neighborhood Processing - Assignment 2 
* Author: Kayhan Karatekeli & Zachary Pierson
* Class: CSC 442 - Digital Image Processing
* Instructor: Dr. John Weiss
* Date: 2/26/15
* Description: This program is designed to apply spacial-domain filters
*              and neighborhood operators to an image.
*
* File: This file contains the noise operators supplied in the noise menu.
************************************************************************/

#include "pa2.h"

/************************************************************************
Function:     Gaussian
Description:  This function adds gaussian noise to an image using the 
              built in function in QT.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Noise_Gaussian( Image &image )
{
    double sd = 8.0;
    if ( !Dialog( "Gaussian Noise" ).Add( sd, "sigma", 0.0, 100.0 ).Show() )
        return false;
    gaussianNoise( image, sd );
    return true;
}

/************************************************************************
Function:     Impulse
Description:  This function adds impulse noise to an image using the 
              built in function in QT.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Noise_Impulse( Image &image )
{
    int p = 64;
    if ( !Dialog( "Impulse Noise" ).Add( p, "probability", 0, 1000 ).Show() )
        return false;
    impulseNoise( image, p );
    return true;
}
