#include "pa2.h"


bool MyApp::Menu_Noise_Gaussian( Image &image )
{
    double sd = 8.0;
    if ( !Dialog( "Gaussian Noise" ).Add( sd, "sigma", 0.0, 100.0 ).Show() )
        return false;
    gaussianNoise( image, sd );
    return true;
}

bool MyApp::Menu_Noise_Impulse( Image &image )
{
    int p = 64;
    if ( !Dialog( "Impulse Noise" ).Add( p, "probability", 0, 1000 ).Show() )
        return false;
    impulseNoise( image, p );
    return true;
}
