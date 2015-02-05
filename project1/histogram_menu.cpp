#include "pa1.h"

//created by Zach & Kayhan
bool MyApp::Menu_Histogram_Display( Image &image )
{
    //displays histogram of image
    displayHistogram(image);
    return true;
}

//created by Zach & Kayhan
bool MyApp::Menu_Histogram_AutoStretch( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice

    //creates a vector of the elements in the image
    vector<unsigned int> histogramE = image.Histogram();
    
    //look up table and variables
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

    //divide by 0 check
    if(max == min)
        return false;

    //sets look up table values
    for(int i = 0; i < 256; i++)
    {
        temp = (255.0/(max - min)) * (i - min);
        LUTauto[i] = temp;
        if(temp > 255)
            LUTauto[i] = 255;
        if(temp < 0)
            LUTauto[i] = 0;
    }

    // apply look up table to image
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
        for ( int c = 0; c < ncols; c++ )
            image[r][c] = LUTauto[ image[r][c] ];

    //updates image
    return true;
}

//modified by Zach & Kayhan
bool MyApp::Menu_Histogram_ModStretch( Image &image )
{
//    //checks image validity
//    if ( image.IsNull() ) return false; // not essential, but good practice
//
//    int min = 0, max = 255;
//    if ( !Dialog( "endpoints" ).Add( min, "left", 0, 255 ).Add( max, "right", 0, 255 ).Show() )
//        return false;
//
//    // create lookup table and sets values
//    byte LUTcontrast[256];
//    for ( int i = 0; i < min; i++ )
//        LUTcontrast[i] = 0;
//    for ( int i = max + 1; i < 256; i++ )
//        LUTcontrast[i] = 255;
//    double slope = 255.0 / (max - min );
//    for ( int i = min; i <= max; i++ )
//        LUTcontrast[i] = (byte)(slope * ( i - min )
//
//    // apply LUT
//    int nrows = image.Height();
//    int ncols = image.Width(); 
//    for ( int r = 0; r < nrows; r++ )
//        for ( int c = 0; c < ncols; c++ )
//            image[r][c] = LUTcontrast[ image[r][c] ];
//
//    //updates image
//    return true;
}

bool MyApp::Menu_Histogram_Equalize( Image &image )
{
    return true;
}

bool MyApp::Menu_Histogram_ClipEqualize( Image &image )
{
    return true;
}
