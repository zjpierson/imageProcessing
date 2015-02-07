/*
               ***** pa1.cpp *****

Program Assignment 1
Class:      Digital Image Processing
Professor:  John M. Weiss, Ph.D.
Room:       McLaury 305
Class Time: 9am M, W, Th


Author: John M. Weiss, Ph.D.
Program written Spring 2015 for SDSM&T CSC442/542 DIP course.


Modifications by: Zach Pierson & Kayhan Karatekeli
Note: Modifications apply to whole program including supplemental header and cpp files. 
      Any modified functions will be denoted above functions individually.
*/
#include "pa1.h"

int main( int argc, char *argv[] )
{
    MyApp obj;
    ImageApp app( argc, argv );
    app.AddActions( &obj );
    return app.Start();
}

