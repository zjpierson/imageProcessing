#include "pa2.h"

//Function given by Dr. Weiss
bool MyApp::Menu_Histogram_Display( Image &image )
{
    displayHistogram( image );
    return true;
}

//Function given by Dr. Weiss
bool MyApp::Menu_Histogram_Stretch( Image &image )
{
    histogramStretch( image );
    return true;
}

//Function given by Dr. Weiss
bool MyApp::Menu_Histogram_Equalize( Image &image )
{
    histogramEqualize( image );
    histogramStretch( image );
    return true;
}
