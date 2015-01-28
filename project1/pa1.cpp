/*
               ***** program1.cpp *****

Demo program to illustrate qtImageLib.
Example 2 shows how to add menu items to the default image viewer.

Author: John M. Weiss, Ph.D.
Written Spring 2015 for SDSM&T CSC442/542 DIP course.

Modifications:
*/

// QtImageLib requires interface as well as implementation
#include "pa1.h"

// typical main function
int main( int argc, char *argv[] )
{
    //check cmd args
    for( int i = 1; i < argc; i++ )
    {
        //open image argv[i];
    }

    MyApp obj;
    ImageApp app( argc, argv );
    app.AddActions( &obj );
    return app.Start();
}

