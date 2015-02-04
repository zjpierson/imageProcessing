#include "pa1.h"

bool MyApp::Menu_Color_DiscretePseudocolor( Image &image )
{
    //Initialize look up grayscale look up table
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    byte LUTdiscrete[256][3];
    int count = 0;
    byte red = 0;
    byte green = 0;
    byte blue = 0;

    for(int i = 0; i < 8; i++)
    {
        //red
        if(i == 1)
        {
            red = 255;
            green = 0;
            blue = 0;
        }
        //orange
        else if(i == 2)
        {
            red = 255;
            green = 128;
            blue = 0;
        }
        //yellow
        else if(i == 3)
        {
            red = 255;
            green = 255;
            blue = 0;
        }
        //green
        else if(i == 4)
        {
            red = 0;
            green = 255;
            blue = 0;
        }
        //blue
        else if(i == 5)
        {
            red = 0;
            green = 0;
            blue = 255;
        }
        //violet
        else if(i == 6)
        {
            red = 128;
            green = 0;
            blue = 128;
        }
        //white
        else if(i == 7)
        {
            red = 255;
            green = 255;
            blue = 255;
        }

        for( int j = count; j < (32+count); j++ )
        {
            LUTdiscrete[j][0] =  red;
            LUTdiscrete[j][1] =  green;
            LUTdiscrete[j][2] =  blue;
        }

        count += 32;
    }

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

