//FIX: log function needs attention!!
//
//

#include "pa1.h"

//Dr. Weiss
//Modifyed by us
bool MyApp::Menu_Palette_Grayscale( Image &image )
{
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    clock_t LUTtime;
    LUTtime = clock();

    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
        {
            // red/green/blue channels can be accessed directly using
            byte red = image[r][c].Red();
            byte green = image[r][c].Green();
            byte blue = image[r][c].Blue();

            // int gray = LUTgrayscale[red][green][blue];
            int gray = 0.30 * red + 0.59 * green + 0.11 * blue + 0.5;

            image[r][c].SetGray( gray );
        }
    }

    LUTtime = clock() - LUTtime;
    std::cout << "time: " << LUTtime << std::endl;

    // return true to update the image
    return true;
}

bool MyApp::Menu_Palette_Negate( Image &image )
{
    if ( image.IsNull() ) return false; // not essential, but good practice
    static byte LUTnegate[256] = {0};

    //initialize negate LUT 
    if ( LUTnegate[128] == 0 )
    {
        for ( int i = 0; i< 256; i++ )
            LUTnegate[i] = 255 - i;
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
            image[r][c] = LUTnegate[image[r][c]];
        }
    }

    LUTtime = clock() - LUTtime;
    std::cout << "time: " << LUTtime << std::endl;

    // return true to update the image
    return true;
}


bool MyApp::Menu_Palette_Threshold( Image &image )
{
    //Initialize look up grayscale look up table
    if ( image.IsNull() ) return false; // not essential, but good practice

    //get threshold from user input
    int threshold = 128;
    if( !Dialog("Threshold").Add(threshold, "set", 0, 255).Show())
            return false;

    clock_t LUTtime;
    LUTtime = clock();

    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
        {
            // red/green/blue channels can be accessed directly using
            byte red = image[r][c].Red();
            byte green = image[r][c].Green();
            byte blue = image[r][c].Blue();

            int gray = 0.30 * red + 0.59 * green + 0.11 * blue + 0.5;

            if( gray < threshold)
                image[r][c].SetGray( 0 );
            else
                image[r][c].SetGray( 255 );

        }
    }

    LUTtime = clock() - LUTtime;
    std::cout << "time: " << LUTtime << std::endl;

    // return true to update the image
    return true;
}

bool MyApp::Menu_Palette_Posterize( Image &image )
{
    //Initialize look up grayscale look up table
    if ( image.IsNull() ) return false; // not essential, but good practice

    //get threshold from user input
    int levels = 8;
    if( !Dialog("Posterize").Add(levels, "Levels", 1, 255).Show())
        return false;

    //create local LUT
    byte LUTpost[256];
    int steps = 255 / (levels - 1);   //need this to be interger division
    for( int i = 0; i < 256; i++ )
        LUTpost[i] = steps * (i/steps); //need integer division

    clock_t LUTtime;
    LUTtime = clock();

    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
        for ( int c = 0; c < ncols; c++ )
            image[r][c] = LUTpost[image[r][c]];

    LUTtime = clock() - LUTtime;
    std::cout << "time: " << LUTtime << std::endl;

    // return true to update the image
    return true;
}

bool MyApp::Menu_Palette_Brightness( Image &image )
{
    //Initialize look up grayscale look up table
    if ( image.IsNull() ) return false; // not essential, but good practice

    //get brightness constant from user input
    int brightness = 0;
    if(!Dialog("Brightness").Add(brightness, "decrease/increase", -255, 255).Show())
        return false;

    //create local LUT
    byte LUTbright[256];
    int temp;
    for( int i = 0; i < 256; i++ )
    {
        temp = i + brightness;
        if(temp < 0)
            temp = 0;
        if(temp > 255)
            temp = 255;
        LUTbright[i] = temp;
    }

    clock_t LUTtime;
    LUTtime = clock();

    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
        for ( int c = 0; c < ncols; c++ )
        {
            // red/green/blue channels can be accessed directly using
            byte red = LUTbright[image[r][c].Red()];
            byte green = LUTbright[image[r][c].Green()];
            byte blue = LUTbright[image[r][c].Blue()];

            image[r][c].SetRGB(red, green, blue);
        }

    LUTtime = clock() - LUTtime;
    std::cout << "time: " << LUTtime << std::endl;

    // return true to update the image
    return true;
}

//Dr. Weiss
bool MyApp::Menu_Palette_Contrast( Image &image )
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

bool MyApp::Menu_Palette_Gamma( Image &image )
{
    //Initialize look up grayscale look up table
    if ( image.IsNull() ) return false; // not essential, but good practice

    //get brightness constant from user input
    double gamma = 1;
    if(!Dialog("Gamma").Add(gamma, "set", 0.01, 10.0).Show())
        return false;

    //create local LUT
    byte LUTgamma[256];
    for( int i = 0; i < 256; i++ )
    {
        LUTgamma[i] = pow( (i/255.0), gamma) * 255;
    }

    clock_t LUTtime;
    LUTtime = clock();

    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
        for ( int c = 0; c < ncols; c++ )
        {
            // red/green/blue channels can be accessed directly using
            byte red = LUTgamma[image[r][c].Red()];
            byte green = LUTgamma[image[r][c].Green()];
            byte blue = LUTgamma[image[r][c].Blue()];

            image[r][c].SetRGB(red, green, blue);
        }

    LUTtime = clock() - LUTtime;
    std::cout << "time: " << LUTtime << std::endl;

    // return true to update the image
    return true;
}

bool MyApp::Menu_Palette_Log( Image &image )
{
    //Initialize look up grayscale look up table
    if ( image.IsNull() ) return false; // not essential, but good practice

    //create local LUT
    byte LUTlog[256];
    for( int i = 0; i < 256; i++ )
        LUTlog[i] = log(i+1) * (255/log(256));

    clock_t LUTtime;
    LUTtime = clock();

    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
        {
            image[r][c] = LUTlog[image[r][c]];
        }
    }

    LUTtime = clock() - LUTtime;
    std::cout << "time: " << LUTtime << std::endl;

    // return true to update the image
    return true;
}
