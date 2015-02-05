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
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice

    double min = 1;                              
    double max = 1;
    int imin = 0;
    int imax = 255;
    int sum = 0;
    int pixPercent = 0;

    if( !Dialog("Stretch").Add(min, "Min", 0, 100).Add(max, "Max", 0, 100).Show())
            return false;


    //creates a vector of the elements in the image
    vector<unsigned int> histogramE = image.Histogram();
    
    //look up table and variables
    byte temp;
    byte LUTstretch[256] = { 0 };
    pixPercent = ((image.Height() * image.Width()) * (min/100));

    //loop though vector and find min percentage pixel values
    for(int i = 0; i < 256; i++)
    {
        sum += histogramE[i];

        if (sum >= pixPercent)
        {
            imin = i;
            break;
        }
    }

    pixPercent = ((image.Height() * image.Width()) * (max/100));
    sum = 0;  //reset the sum values
    //find max percentage pixel values
    for(int i = 255; i >= 0; i--)
    {
        sum += histogramE[i];

        if (sum >= pixPercent)
        {
            imax = i;
            break;
        }
    }

    //divide by 0 check && no crossing min and max
    if(imax <= imin)
        return false;
    
    //clips the leading and trailing values
    for(int i = 0; i < imin; i++)
        LUTstretch[i] = 0;
    for(int i = 255; i >= imax; i--)
        LUTstretch[i] = 255;

    //sets look up table values
    for(int i = imin; i < imax; i++)
    {
        temp = (255.0/(imax - imin)) * (i - imin);
        LUTstretch[i] = temp;
        if(temp > 255)
            LUTstretch[i] = 255;
        if(temp < 0)
            LUTstretch[i] = 0;
    } 

    // apply look up table to image
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
        for ( int c = 0; c < ncols; c++ )
            image[r][c] = LUTstretch[ image[r][c] ];

    //updates image
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
