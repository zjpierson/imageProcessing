#include "pa1.h"

bool MyApp::Menu_Color_DiscretePseudocolor( Image &image )
{
    //Initialize look up grayscale look up table
    if ( image.IsNull() ) return false; // not essential, but good practice

    //create local LUT
    byte LUTdiscrete[256][3];
    double steps = (255/8);
    int count = 0;
    int red = 0;
    int green = 0;
    int blue = 0;
    
    while(count < 256)
    {
        if( steps+count > 256 )
            break;

        for( int i = count; i < (steps+count); i++ )
        {
            LUTdiscrete[i][0] =  red;
            LUTdiscrete[i][1] =  green;
            LUTdiscrete[i][2] =  blue;
        }
        count += steps;
        
        //red
        if(count < (2*steps) && count >= steps)
        {
            red = 255;
            green = 0;
            blue = 0;
        }
        //orange
        if(count < (3*steps) && count >= (2*steps))
        {
            red = 255;
            green = 128;
            blue = 0;
        }
        //yellow
        if(count < (4*steps) && count >= (3*steps))
        {
            red = 255;
            green = 255;
            blue = 0;
        }
        //green
        if(count < (5*steps) && count >= (4*steps))
        {
            red = 0;
            green = 255;
            blue = 0;
        }
        //blue
        if(count < (6*steps) && count >= (5*steps))
        {
            red = 0;
            green = 0;
            blue = 255;
        }
        //violet
        if(count < (7*steps) && count >= (6*steps))
        {
            red = 128;
            green = 0;
            blue = 128;
        }
        //white
        if(count < (8*steps) && count >= (7*steps))
        {
            red = 255;
            green = 255;
            blue = 255;
        }
    }
    //   LUTdiscrete[i] = steps * (i/(int)steps); //need integer division

    clock_t LUTtime;
    LUTtime = clock();

    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
        {
            image[r][c].SetRed(LUTdiscrete[image[r][c]][0]);
            image[r][c].SetGreen(LUTdiscrete[image[r][c]][1]);
            image[r][c].SetBlue(LUTdiscrete[image[r][c]][2]);
        }
    }

    LUTtime = clock() - LUTtime;
    std::cout << "time: " << LUTtime << std::endl;

    // return true to update the image
    return true;
}

bool MyApp::Menu_Color_ContinuousPseudocolor( Image &image )
{
    return true;
}
