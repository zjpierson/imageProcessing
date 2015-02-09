/*
               ***** pa2.cpp *****

Demo program to illustrate qtImageLib.
Example 2 shows how to add menu items to the default image viewer.

Author: John M. Weiss, Ph.D.
Written Spring 2015 for SDSM&T CSC442/542 DIP course.

Modifications:
*/

// QtImageLib requires interface (example2.h) as well as implementation (example2.cpp)
#include "pa2.h"

// typical main function
int main( int argc, char *argv[] )
{
    MyApp obj;
    ImageApp app( argc, argv );
    app.AddActions( &obj );
    return app.Start();
}
