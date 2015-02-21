#include "pa2.h"

bool MyApp::Menu_Filter_Smoothing_3x3( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int row = 0;
    int col = 0;
    int i = 0;
    int sum = 0;
    int rbound = 0;
    int cbound = 0;

    //create filter mask matrix
    int matrixArr[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1};

    //make copy of image as to not destroy original information
    Image temp(image);
    
    for ( int r = 1; r < nrows - 1; r++ )
    {
        for ( int c = 1; c < ncols - 1; c++ )
        {
            //neighborhood boundries
            rbound = r - 1;
            cbound = c - 1;
            
            //begins the loop through inner filter
            for(row = r-1; row < (3+rbound); row++)
            {
                for(col = c-1; col < (3+cbound); col++)
                {
                    sum += matrixArr[i] * image[row][col];
                    i++;
                }
            }
            
            //set the resulting pixel to a temporary image
            temp[r][c] = (sum/16);

            //reset neighborhood variables
            i = 0;
            sum = 0;
        }
    }

    image = temp;

    // return true to update the image
    return true;
}

bool MyApp::Menu_Filter_Sharpening_3x3( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int row = 0;
    int col = 0;
    int i = 0;
    int sum = 0;
    int rbound = 0;
    int cbound = 0;

    //create filter mask matrix
    int matrixArr[9] = {0, -1, 0, -1, 5, -1, 0, -1, 0};

    //make copy of image as to not destroy original information
    Image temp(image);
    
    for ( int r = 1; r < nrows - 1; r++ )
    {
        for ( int c = 1; c < ncols - 1; c++ )
        {
            //neighborhood boundries
            rbound = r - 1;
            cbound = c - 1;
            
            //begins the loop through inner filter
            for(row = r-1; row < (3+rbound); row++)
            {
                for(col = c-1; col < (3+cbound); col++)
                {
                    sum += matrixArr[i] * image[row][col];
                    i++;
                }
            }
            
            //set the resulting pixel to a temporary image
            if(sum < 0)
                temp[r][c] = 0;
            else if(sum > 255)
                temp[r][c] = 255;
            else
                temp[r][c] = sum;

            //reset neighborhood variables
            i = 0;
            sum = 0;
        }
    }

    image = temp;

    // return true to update the image
    return true;
}

bool MyApp::Menu_Filter_PlusMedian( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int row = 0;
    int col = 0;
    int i = 0;
    int j = 0;
    int rbound = 0;
    int cbound = 0;

    //create filter mask matrix
    int matrixA[9] = {0, 1, 0, 1, 1, 1, 0, 1, 0};
    int med[5] = {0};

    //make copy of image as to not destroy original information
    Image temp(image);
    
    for ( int r = 1; r < nrows - 1; r++ )
    {
        for ( int c = 1; c < ncols - 1; c++ )
        {
            //neighborhood boundries
            rbound = r - 1;
            cbound = c - 1;
            
            //begins the loop through inner filter
            for(row = r-1; row < (3+rbound); row++)
            {
                for(col = c-1; col < (3+cbound); col++)
                {
                    if(matrixA[i] == 1)
                    {
                        med[j] = image[row][col];
                        j++;
                    }
                    i++;
                }
            }
            
            //find median and set temp image[r][c] to that pixel
            temp[r][c] = median(med, 5);

            //reset neighborhood variables
            i = 0;
            j = 0;
        }
    }

    image = temp;

    // return true to update the image
    return true;
}

int MyApp::median(int array[], int size)
{
    int j = 0;
    int temp = 0;

    for(int i = 1; i < size; i++)
    {
        j = i;

        while(j > 0 && array[j-1] > array[j])    
        {
            temp = array[j];
            array[j] = array[j-1];
            array[j-1] = temp;
            j--;
        }
    }

    return array[size/2];
}

bool MyApp::Menu_Filter_NoiseCleaning( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    int threshold = 32;
    if( !Dialog("Threshold").Add(threshold, "set", 0, 255).Show())
            return false;

    int avg = 0;

    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int row = 0;
    int col = 0;
    int rbound = 0;
    int cbound = 0;

    //make copy of image as to not destroy original information
    Image temp(image);
    
    for ( int r = 1; r < nrows - 1; r++ )
    {
        for ( int c = 1; c < ncols - 1; c++ )
        {
            //neighborhood boundries
            rbound = r - 1;
            cbound = c - 1;
            
            //begins the loop through inner filter (neighborhood)
            for(row = r-1; row < (3+rbound); row++)
            {
                for(col = c-1; col < (3+cbound); col++)
                {
                    //add up all the pixels except for the center pixel
                    if( row == r && col == c )
                        continue;
                    avg += image[row][col];
                }
            }
            
            //compute avg (devide sum by 8)
            avg /= 8;

            //do thresholding 
            if( abs(image[r][c] - avg) > threshold )
                temp[r][c] = avg;

            //reset loop variables
            avg = 0;
        }
    }

    image = temp;

    // return true to update the image
    return true;
}

bool MyApp::Menu_Filter_Mean( Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    int n = 3;
    int nrows = image.Height();
    int ncols = image.Width();
    int row = 0;
    int col = 0;
    int sum = 0;
    int border = 1;
    queue<int> startQ;
    queue<int> normalQ;
    stack<int> endStack;

    //get input for nxn neighborhood
    if( !getParams(n) )
            return false;

    //if n is even, add 1 to have a center pixel
    if( n % 2 == 0)
        n++;

    //get number of pixels to the center pixel
    border = abs(n/2);

    //make copy of image as to not destroy original information
    Image temp(image);

    //make 2 passes using seperable 1d arrays
    //first pass though image: iterate across columns
    for ( int r = 0; r < nrows; r++ )
    {
        for ( int c = 0; c < ncols; c++ )
        {   
            //Middle case:
            if( (c-border > 0) && (c+border < ncols) )
            {
                sum -= normalQ.front();
                normalQ.pop();

                normalQ.push(temp[r][c]);
                sum += temp[r][c];

                image[r][c-border] = (sum/n);
            }
            //Beginning case:
            else if( c-border <= 0 )
            {
                if(startQ.size() < border)
                {
                    startQ.push(temp[r][c]);
                    endStack.push(temp[r][c]);

                }
                else
                {
                    popContainer(endStack, startQ, normalQ, sum);
                    normalQ.push(temp[r][c]);
                    sum += temp[r][c];
                    image[r][c-border] = (sum/n);
                }
            }














            //set the resulting pixel to a temporary image
            temp[r][c] = sum;

            //reset neighborhood variables
            sum = 0;
        }
    }
    

    //second pass though image: rows
    
    for ( int r = border; r < nrows - border; r++ )
    {
        for ( int c = border; c < ncols - border; c++ )
        {
            //neighborhood boundries
            rbound = r - border;
            cbound = c - border;
            
            //begins the loop through inner filter
            for(row = r-border; row < (n+rbound); row++)
            {
                for(col = c-border; col < (n+cbound); col++)
                {
                    sum += image[row][col];
                }
            }
            
            //set the resulting pixel to a temporary image
            temp[r][c] = (sum/(n*n));

            //reset neighborhood variables
            sum = 0;
        }
    }

    image = temp;

    // return true to update the image
    return true;
}

int popContainer(stack<int> endStack, queue<int> startQ, queue<int> normalQ, int sum)
{
    while(!endStack.empty())
    {
        sum += endStack.top();
        normalQ.push(endStack.top());
        endStack.pop();
    }
    while(!startQ.empty())
    {
        sum += startQ.front();
        normalQ.push(startQ.front());
        startQ.pop();
    }
}

bool MyApp::Menu_Filter_Median( Image &image )
{
    return true;
}

bool MyApp::Menu_Filter_Minimum( Image &image )
{
    return true;
}

bool MyApp::Menu_Filter_Maximum( Image &image )
{
    return true;
}

bool MyApp::Menu_Filter_Range( Image &image )
{
    return true;
}

bool MyApp::Menu_Filter_StandardDeviation( Image &image )
{
    return true;
}

bool MyApp::Menu_Filter_Emboss(Image &image )
{
    //checks image validity
    if ( image.IsNull() ) return false; // not essential, but good practice
    
    //adjust rows and columns because of the 3x3 neighborhood
    int nrows = image.Height();
    int ncols = image.Width();
    int row = 0;
    int col = 0;
    int i = 0;
    int sum = 0;
    int rbound = 0;
    int cbound = 0;

    //create filter mask matrix
    int matrixArr[9] = {0, 0, 0, 0, 1, 0, 0, 0, -1};

    //make copy of image as to not destroy original information
    Image temp(image);
    
    for ( int r = 1; r < nrows - 1; r++ )
    {
        for ( int c = 1; c < ncols - 1; c++ )
        {
            //neighborhood boundries
            rbound = r - 1;
            cbound = c - 1;
            
            //begins the loop through inner filter
            for(row = r-1; row < (3+rbound); row++)
            {
                for(col = c-1; col < (3+cbound); col++)
                {
                    sum += matrixArr[i] * image[row][col];
                    i++;
                }
            }
            
            temp[r][c] = (sum + 255)/2;

            //reset neighborhood variables
            i = 0;
            sum = 0;
        }
    }

    image = temp;

    // return true to update the image

    return true;
}

bool MyApp::Menu_Filter_Gaussian( Image &image )
{
    return true;
}

