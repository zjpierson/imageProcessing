#include "pa1.h"

//created by Zach & Kayhan
/************************************************************************
Function:     Display
Description:  This function simply calls the displayHistogram function
              of QtImageLib.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Histogram_Display( Image &image )
{
    //displays histogram of image
    displayHistogram(image);
    return true;
}

//created by Zach & Kayhan
/************************************************************************
Function:     Auto_Stretch
Description:  This function stretches the histogram just enough to have
              the full range of pixel intensities. This is achived by
              first finding the minimum and maximum pixel intensities of
              the image. With that we can populate our Look Up Table with
              updated histogram information. This point process is then
              applied to every pixel in the image.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
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
        LUTauto[i] = (255.0/(max - min)) * (i - min);
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
/************************************************************************
Function:     ModStretch
Description:  This function asks the user for a percentage of pixels to
              ignore from both ends. We first find the number of pixels
              to ignore and then loop though the histogram until we have
              iterated though that number of pixels. We store the integer
              min and max values as positions. This is used to streatch 
              the histogram up to those points. A linear ramp is used on
              the rest of the histogram. We apply the LUT to the image as
              a point process and return true;
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
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
        LUTstretch[i] = (255.0/(imax - imin)) * (i - imin);
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

/************************************************************************
Function:     Equalize
Description:  This function goes through the histogram data and applies
              the Cumulative Distribution Function CDF to create the
              Look Up Table. The LUT is then applied as a point process
              the the individual pixels in the image.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Histogram_Equalize( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice

    long long sum = 0;
    long long totalPxl = image.Height() * image.Width();

    //creates a vector of the elements in the image
    vector<unsigned int> histogramE = image.Histogram();
    
    //look up table 
    byte LUTcdf[256] = { 0 };

    //loop though vector and create LUT
    for(int i = 0; i < 256; i++)
    {
        sum += histogramE[i];
        LUTcdf[i] = sum * (255.0/totalPxl);
    }

    // apply look up table to image
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
        for ( int c = 0; c < ncols; c++ )
            image[r][c] = LUTcdf[ image[r][c] ];

    //updates image
    return true;
}

/************************************************************************
Function:     ClipEqualize
Description:  This function is very similar to the Equalize function
              except that it clips a percentage of the histogram before
              creating the Look Up Table. The user specifies the precent.
              A loop goes though the histogram values and clips them
              if they are above that percentage of the total pixels. The
              new total number of pixels is then stored in order to do 
              the computation that the Equalize function does.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Histogram_ClipEqualize( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice

    long long sum = 0;
    long long totalPxl = image.Height() * image.Width();
    double percent = 1;
    long cut;

    if( !Dialog("Clip Threshold").Add(percent, "percent", 0, 100).Show())
            return false;

    cut = totalPxl * percent;

    //creates a vector of the elements in the image
    vector<unsigned int> histogramE = image.Histogram();

    for(int i = 0; i < 256; i++)
    {
        if( histogramE[i] > cut )
            histogramE[i] = cut;
    }
    //add new number of pixles
    for(int i = 0; i < 256; i++)
    {
        sum += histogramE[i];
    }
    totalPxl = sum;
    sum = 0;
    
    //look up table 
    byte LUTcdf[256] = { 0 };

    //loop though vector and create LUT
    for(int i = 0; i < 256; i++)
    {
        sum += histogramE[i];
        LUTcdf[i] = sum * (255.0/totalPxl);
    }

    // apply look up table to image
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
        for ( int c = 0; c < ncols; c++ )
            image[r][c] = LUTcdf[ image[r][c] ];

    //updates image
    return true;
}
