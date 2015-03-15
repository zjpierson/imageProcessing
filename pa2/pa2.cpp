/************************************************************************
* Program: Neighborhood Processing - Assignment 2 
* Author: Kayhan Karatekeli & Zachary Pierson
* Class: CSC 442 - Digital Image Processing
* Instructor: Dr. John Weiss
* Date: 2/26/15
* Description: This program is designed to apply spacial-domain filters
*              and neighborhood operators to an image.
*
* File: This file is the main interface for the whole program.
* NOTE: This interface was written by Dr. John Weiss in Spring 2015 
*       for SDSM&T CSC442/542 DIP course.
************************************************************************/

#include "pa2.h"

/************************************************************************
Function:     Main
Description:  This function runs and controls the program. 
Parameters:   param[in] argc - Number of arguments supplied on cmdline. 
              param[in] argv - Array of ptrs to args supplied on cmdline.
              param[out] app.Start() - Runs the image processing
                                       application QT 
************************************************************************/
int main( int argc, char *argv[] )
{
    MyApp obj;
    ImageApp app( argc, argv );
    app.AddActions( &obj );
    return app.Start();
}
