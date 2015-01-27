#include "pa1.h"
unsigned char MyApp::LUTgrayscale[256][256][256]; 
unsigned char MyApp::LUTnegate[256];

//Dr. Weiss
//Modifyed by us
bool MyApp::Menu_Palette_Grayscale( Image &image )
{
    if ( image.IsNull() ) return false; // not essential, but good practice
    if(!grayscaleINIT)
    {
        init_LUTgrayscale();
        grayscaleINIT = true;
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
            unsigned char red = image[r][c].Red();
            unsigned char green = image[r][c].Green();
            unsigned char blue = image[r][c].Blue();

            int gray = LUTgrayscale[red][green][blue];

            image[r][c].SetGray( gray );
        }
    LUTtime = clock() - LUTtime;

    std::cout << "time: " << LUTtime << std::endl;

    // return true to update the image
    return true;
}

void MyApp::init_LUTgrayscale()
{
    //Compute Look Up Table for grayscale
    for ( int r = 0; r < 256; r++)
        for ( int g = 0; g < 256; g++)
            for ( int b = 0; b < 256; b++)
                LUTgrayscale[r][g][b] = ( .3*r + .59*g + .11*b);

}

bool MyApp::Menu_Palette_Negate( Image &image )
{
    if ( image.IsNull() ) return false; // not essential, but good practice
    if(!negateINIT)
    {
        init_LUTnegate();
        negateINIT = true;
    }

    clock_t LUTtime;
    LUTtime = clock();

    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
        for ( int c = 0; c < ncols; c++ )
        {
            image[r][c].SetRed( LUTnegate[image[r][c].Red()] );
            image[r][c].SetGreen( LUTnegate[image[r][c].Green()] );
            image[r][c].SetBlue( LUTnegate[image[r][c].Blue()] );
        }

    LUTtime = clock() - LUTtime;
    std::cout << "time: " << LUTtime << std::endl;

    // return true to update the image
    return true;
}

void MyApp::init_LUTnegate()
{
    for ( int i = 0; i< 256; i++ )
        LUTnegate[i] = 255 - i;
}

bool MyApp::Menu_Palette_Threshold( Image &image )
{
    //Initialize look up grayscale look up table
    if ( image.IsNull() ) return false; // not essential, but good practice
    if(!grayscaleINIT)
    {
        init_LUTgrayscale();
        grayscaleINIT = true;
    }

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
        for ( int c = 0; c < ncols; c++ )
        {
            // red/green/blue channels can be accessed directly using
            unsigned char red = image[r][c].Red();
            unsigned char green = image[r][c].Green();
            unsigned char blue = image[r][c].Blue();

            if( LUTgrayscale[red][green][blue] < threshold)
                image[r][c].SetGray( 0 );
            else
                image[r][c].SetGray( 255 );

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
    unsigned char LUTpost[256];
    int steps = 255 / levels;   //need this to be interger division
    for( int i = 0; i < 256; i++ )
    {
        LUTpost[i] = steps * (i/steps); //need integer division
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
            unsigned char red = LUTpost[image[r][c].Red()];
            unsigned char green = LUTpost[image[r][c].Green()];
            unsigned char blue = LUTpost[image[r][c].Blue()];

            image[r][c].SetRGB(red, green, blue);
        }

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
    unsigned char LUTbright[256];
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
            unsigned char red = LUTbright[image[r][c].Red()];
            unsigned char green = LUTbright[image[r][c].Green()];
            unsigned char blue = LUTbright[image[r][c].Blue()];

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
    // int imin = 32, imax = 224;
    int min = 0, max = 255;
    if ( !Dialog( "endpoints" ).Add( min, "left", 0, 255 ).Add( max, "right", 0, 255 ).Show() )
        return false;

    // create lookup table
    unsigned char LUTcontrast[256];
    for ( int i = 0; i < min; i++ )
        LUTcontrast[i] = 0;
    for ( int i = max + 1; i < 256; i++ )
        LUTcontrast[i] = 255;
    double slope = 255.0 / (max - min );
    for ( int i = min; i <= max; i++ )
        LUTcontrast[i] = (unsigned char)(slope * ( i - min ));

    // apply LUTcontrastette
    int nrows = image.Height();
    int ncols = image.Width();
    image.ToYIQ();
    for ( int r = 0; r < nrows; r++ )
        for ( int c = 0; c < ncols; c++ )
            image[r][c].yiq.y = LUTcontrast[ image[r][c].yiq.y ];

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
    unsigned char LUTgamma[256];
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
            unsigned char red = LUTgamma[image[r][c].Red()];
            unsigned char green = LUTgamma[image[r][c].Green()];
            unsigned char blue = LUTgamma[image[r][c].Blue()];

            image[r][c].SetRGB(red, green, blue);
        }

    LUTtime = clock() - LUTtime;
    std::cout << "time: " << LUTtime << std::endl;

    // return true to update the image
    return true;
}

bool MyApp::Menu_Palette_Log( Image &image )
{
    return true;
}


//bool MyApp::Menu_Palette_Posterize( Image &image )
//{
//    //Initialize look up grayscale look up table
//    if ( image.IsNull() ) return false; // not essential, but good practice
//
//    //get threshold from user input
//    int levels = 8;
//    if( !getParams(levels))
//        return false;
//
//    //create local LUT
//    unsigned char LUTpost[256];
//    int steps = 255 / levels;   //need this to be interger division
//    for( int i = 0; i < levels; i++ )
//    {
//        LUTpost[i] = steps * (i/steps); //need integer division
//    }
//
//    clock_t LUTtime;
//    LUTtime = clock();
//
//    // convert RGB values to HSI intensities
//    int nrows = image.Height();
//    int ncols = image.Width();
//    for ( int r = 0; r < nrows; r++ )
//        for ( int c = 0; c < ncols; c++ )
//        {
//            // red/green/blue channels can be accessed directly using
//            unsigned char red = LUTpost[image[r][c].Red()];
//            unsigned char green = LUTpost[image[r][c].Green()];
//            unsigned char blue = LUTpost[image[r][c].Blue()];
//
//            image[r][c].SetRGB(red, green, blue);
//        }
//
//    LUTtime = clock() - LUTtime;
//    std::cout << "time: " << LUTtime << std::endl;
//
//    // return true to update the image
//    return true;
//}
