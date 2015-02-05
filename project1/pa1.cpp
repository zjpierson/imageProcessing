/*
               ***** program1.cpp *****

Demo program to illustrate qtImageLib.

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

