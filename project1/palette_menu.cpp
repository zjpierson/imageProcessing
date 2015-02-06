#include "pa1.h"

//modified by Zach & Kayhan
/************************************************************************
Function:     Greyscale 
Description:  This function converts an image to greyscale.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Palette_Grayscale( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();
    
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
        {
            //saves RGB values respectively
            byte red = image[r][c].Red();
            byte green = image[r][c].Green();
            byte blue = image[r][c].Blue();

            //sets weighted values to create greyscale
            int gray = 0.30 * red + 0.59 * green + 0.11 * blue + 0.5;

            //sets the image to greyscale
            image[r][c].SetGray( gray );
        }
    }

    // return true to update the image
    return true;
}

//modified by Zach & Kayhan
/************************************************************************
Function:     Negate 
Description:  This function negates the image.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
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

    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();

    //sets image values to lookup table
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
            image[r][c] = LUTnegate[image[r][c]];
    }

    // return true to update the image
    return true;
}

//modified by Zach & Kayhan
/************************************************************************
Function:     Threshold  
Description:  This function allows the user to set a threshold value that
              converts the image to a binary image using the input as the
              median.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL or user
                                 enters an invalid value.
************************************************************************/
bool MyApp::Menu_Palette_Threshold( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice

    //get threshold from user input
    int threshold = 128;
    if( !Dialog("Threshold").Add(threshold, "set", 0, 255).Show())
            return false;

    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();

    //sets image with new values
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
        {
            //saves RGB values respectively
            byte red = image[r][c].Red();
            byte green = image[r][c].Green();
            byte blue = image[r][c].Blue();

            //changes image to greyscale
            int gray = 0.30 * red + 0.59 * green + 0.11 * blue + 0.5;

            //clips values if outside range: 0-255
            if( gray < threshold)
                image[r][c].SetGray( 0 );
            else
                image[r][c].SetGray( 255 );

        }
    }

    // return true to update the image
    return true;
}

//modified by Zach & Kayhan
/************************************************************************
Function:     Posterize
Description:  This function allows the user to select the number of
              levels they wish to use for the posterize. Then the image 
              intensities are blocked according to the levels they 
              desire.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL or user
                                 enters an invalid value.
************************************************************************/
bool MyApp::Menu_Palette_Posterize( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice

    //get threshold from user input
    int levels = 8;
    if( !Dialog("Posterize").Add(levels, "Levels", 1, 255).Show())
        return false;

    //create lookup table
    byte LUTpost[256];

    //establishes increment for number of levels specified
    int steps = 255 / (levels - 1);

    //sets lookup table to approperiate values
    for( int i = 0; i < 256; i++ )
        LUTpost[i] = steps * (i/steps); //need integer division

    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();

    //changes image values with LUT
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
            image[r][c] = LUTpost[image[r][c]];
    }
    // return true to update the image
    return true;
}

//modified by Zach & Kayhan
/************************************************************************
Function:     Brightness
Description:  This function increases/decreases the intensity or
              brightness values of the image.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL or user
                                 enters an invalid value.
************************************************************************/
bool MyApp::Menu_Palette_Brightness( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice

    //get brightness constant from user input
    int brightness = 0;
    if(!Dialog("Brightness").Add(brightness, "decrease/increase", -255, 255).Show())
        return false;

    //sets lookup table to approperiate values
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

    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();
    
    //changes image values with LUT
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
        {
            //saves RGB values respectively
            byte red = LUTbright[image[r][c].Red()];
            byte green = LUTbright[image[r][c].Green()];
            byte blue = LUTbright[image[r][c].Blue()];

            //sets image intensities
            image[r][c].SetRGB(red, green, blue);
        }
    }
    // return true to update the image
    return true;
}

//modified by Zach & Kayhan
/************************************************************************
Function:     Contrast
Description:  This function changes the contrast of the image.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL or user
                                 enters an invalid value.
************************************************************************/
bool MyApp::Menu_Palette_Contrast( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice

    int min = 0, max = 255;
    
    //allows user to input values
    if ( !Dialog( "endpoints" ).Add( min, "left", 0, 255 ).Add( max, "right", 0, 255 ).Show() )
        return false;

    // create lookup table and sets them accordingly
    byte LUTcontrast[256];
    for ( int i = 0; i < min; i++ )
        LUTcontrast[i] = 0;
    for ( int i = max + 1; i < 256; i++ )
        LUTcontrast[i] = 255;

    double slope = 255.0 / (max - min );
    for ( int i = min; i <= max; i++ )
        LUTcontrast[i] = (byte)(slope * ( i - min ));

    // apply LUTcontrast
    int nrows = image.Height();
    int ncols = image.Width();
    
    //sets image values to LUT
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
            image[r][c] = LUTcontrast[ image[r][c] ];
    }
    // return true to update the image
    return true;
}

//created by Zach & Kayhan
/************************************************************************
Function:     Gamma 
Description:  This function manipulates the gamma values of the image.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL.
************************************************************************/
bool MyApp::Menu_Palette_Gamma( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice

    //get brightness constant from user input
    double gamma = 1;
    if(!Dialog("Gamma").Add(gamma, "set", 0.01, 10.0).Show())
        return false;

    //create local LUT
    byte LUTgamma[256];
    for( int i = 0; i < 256; i++ )
        LUTgamma[i] = pow( (i/255.0), gamma) * 255;

    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
        {
            //saves RGB values respectively
            byte red = LUTgamma[image[r][c].Red()];
            byte green = LUTgamma[image[r][c].Green()];
            byte blue = LUTgamma[image[r][c].Blue()];

            //sets image intensities
            image[r][c].SetRGB(red, green, blue);
        }
    }
    // return true to update the image
    return true;
}

//created by Zach & Kayhan
/************************************************************************
Function:     Log 
Description:  This function takes the log of the intensity values for
              the image.
Parameters:   param[in]  image - The image being converted.
              param[out] true  - Updates the image upon completion.
              param[out] false - Exits function if image is NULL or user
                                 enters an invalid value.
************************************************************************/
bool MyApp::Menu_Palette_Log( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice

    //create local LUT and sets the values
    byte LUTlog[256];
    for( int i = 0; i < 256; i++ )
        LUTlog[i] = log(i+1) * (255/log(256));

    // convert RGB values to HSI intensities
    int nrows = image.Height();
    int ncols = image.Width();
    
    //sets image to LUT values
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
            image[r][c] = LUTlog[image[r][c]];
    }

    // return true to update the image
    return true;
}
