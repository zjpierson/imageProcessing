#include "pa2.h"

//Function supplied by Dr. Weiss
bool MyApp::Menu_Palette_Threshold( Image &image )
{
    int thresh = 128;
    if ( !Dialog( "grayscale threshold" ).Add( thresh, "Threshold", 1, 255 ).Show() )
        return false;
    binaryThreshold( image, thresh );
    return true;
}

bool MyApp::Menu_Palette_Embossing( Image &image )
{

    return true;
}

//Function supplied by Dr. Weiss
bool MyApp::Menu_Palette_Grayscale( Image &image )
{
    grayscale( image );
    return true;
}
