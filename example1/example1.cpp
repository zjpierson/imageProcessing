/*
               ***** example1.cpp *****

Demo program to illustrate qtImageLib.
Default is to create an image viewer.

Author: John M. Weiss, Ph.D.
Written Spring 2015 for SDSM&T CSC442/542 DIP course.

Modifications:
*/

#include <qtimagelib.h>

// typical main function
int main( int argc, char *argv[] )
{
    QObject obj;
    ImageApp app( argc, argv );
    app.AddActions( &obj );
    return app.Start();
}
