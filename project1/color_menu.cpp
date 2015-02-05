#include "pa1.h"

//created by Zach & Kayhan
bool MyApp::Menu_Color_DiscretePseudocolor( Image &image )
{
    //checks image for validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //variables
    byte LUTdiscrete[256][3] = { 0 };
    int count = 0;
    byte red = 0;
    byte green = 0;
    byte blue = 0;

    //loops through each of the 8 layers and sets a specific color
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

        //sets the values of the look up table
        for( int j = count; j < (32+count); j++ )
        {
            LUTdiscrete[j][0] =  red;
            LUTdiscrete[j][1] =  green;
            LUTdiscrete[j][2] =  blue;
        }

        count += 32;
    }

    //loops through image and sets the colors accordingly
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
        {
            int pix = image[r][c]; //ensures no race conditions
            image[r][c].SetRed( LUTdiscrete[pix][0] );
            image[r][c].SetGreen( LUTdiscrete[pix][1] );
            image[r][c].SetBlue( LUTdiscrete[pix][2] );
        }
    }

    // return true to update the image
    return true;
}

bool MyApp::Menu_Color_ContinuousPseudocolor( Image &image )
{
    //checks image for validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //create LUTcont
    byte LUTcont[256][3] = { 0 };

    //set the LUT values
    for(int i = 0; i < 256; i++)
    {
        //red
        LUTcont[i][0] = i;
    }
    for(int i = 0; i < 128; i++)
    {
        //green
        LUTcont[i][1] = (2*i);
    }
    for(int i = 0; i < 128; i++)
    {
        //green
        LUTcont[i+128][1] = 255 - (i*2);
    }
    for(int i = 0; i < 256; i++)
    {
        //blue
        LUTcont[i][2] = 255 - i;
    }

    //loops through image and sets the colors accordingly
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
        {
            int pix = image[r][c]; //ensures no race conditions
            image[r][c].SetRed( LUTcont[pix][0] );
            image[r][c].SetGreen( LUTcont[pix][1] );
            image[r][c].SetBlue( LUTcont[pix][2] );
        }
    }

    // return true to update the image
    return true;
}

bool MyApp::Menu_Color_American( Image &image )
{
    //checks image for validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //variables
    byte LUTamerican[256][3] = { 0 };
    int count = 0;
    byte red = 0;
    byte green = 0;
    byte blue = 0;

    //loops through each of the 3 layers and sets a specific color
    for(int i = 0; i < 4; i++)
    {
        //red
        if(i == 1)
        {
            red = 255;
            green = 0;
            blue = 0;
        }
        //white
        else if(i == 2)
        {
            red = 255;
            green = 255;
            blue = 255;
        }
        //blue
        else if(i == 3)
        {
            red = 0;
            green = 0;
            blue = 255;
        }

        //sets the values of the look up table
        for( int j = count; j < (64+count); j++ )
        {
            LUTamerican[j][0] =  red;
            LUTamerican[j][1] =  green;
            LUTamerican[j][2] =  blue;
        }

        count += 64;
    }

    //loops through image and sets the colors accordingly
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
        {
            int pix = image[r][c]; //ensures no race conditions
            image[r][c].SetRed( LUTamerican[pix][0] );
            image[r][c].SetGreen( LUTamerican[pix][1] );
            image[r][c].SetBlue( LUTamerican[pix][2] );
        }
    }

    // return true to update the image
    return true;
}
