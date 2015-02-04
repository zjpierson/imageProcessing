#include "pa1.h"

bool MyApp::Menu_Histogram_Display( Image &image )
{
    displayHistogram(image);
    return true;
}

bool MyApp::Menu_Histogram_AutoStretch( Image &image )
{
    //Initialize look up grayscale look up table
    if ( image.IsNull() ) return false; // not essential, but good practice

    vector<unsigned int> histogramE = image.Histogram();
    byte LUTauto[256];
    unsigned int min = 0;
    unsigned int max = 255;
    byte temp;

    //loop though vector and find min and max pixel values
    for(int i = 0; i < histogramE.size(); i++)
    {
        if(histogramE[i] == 0)
            min++;
        else
            break;
    }
    for(int i = (histogramE.size() - 1); i >= 0; i--)
    {
        if(histogramE[i] == 0)
            max--;
        else
            break;
    }

    //devide by 0 check
    if(max == min)
        return false;

    for(int i = 0; i < 256; i++)
    {
        temp = (255.0/(max - min)) * (i - min);
        if(temp > 255)
            LUTauto[i] = 255;
        if(temp < 0)
            LUTauto[i] = 0;
    }

    // apply LUTauto
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
        for ( int c = 0; c < ncols; c++ )
            image[r][c] = LUTauto[ image[r][c] ];

    return true;
}

bool MyApp::Menu_Histogram_ModStretch( Image &image )
{
    //Initialize look up grayscale look up table
    if ( image.IsNull() ) return false; // not essential, but good practice

    // int imin = 32, imax = 224;
    int min = 0, max = 255;
    if ( !Dialog( "endpoints" ).Add( min, "left", 0, 255 ).Add( max, "right", 0, 255 ).Show() )
        return false;

    // create lookup table
    byte LUTcontrast[256];
    for ( int i = 0; i < min; i++ )
        LUTcontrast[i] = 0;
    for ( int i = max + 1; i < 256; i++ )
        LUTcontrast[i] = 255;
    double slope = 255.0 / (max - min );
    for ( int i = min; i <= max; i++ )
        LUTcontrast[i] = (byte)(slope * ( i - min ));

    // apply LUTcontrastette
    int nrows = image.Height();
    int ncols = image.Width();
//    image.ToYIQ();
    for ( int r = 0; r < nrows; r++ )
        for ( int c = 0; c < ncols; c++ )
            image[r][c] = LUTcontrast[ image[r][c] ];

    return true;
}

bool MyApp::Menu_Histogram_Equalize( Image &image )
{
    return true;
}

bool MyApp::Menu_Histogram_ClipEqualize( Image &image )
{
    return true;
}
