#include "ComplexPlane.h"

///helper functions to be unit tested
///map from pixels to complex plane
double mapRange(double n, double fromLow, double fromHigh, double toLow, double toHigh)
{
  return toLow+((double)n - fromLow)*(toHigh-toLow)/(fromHigh-fromLow);
}
///write rgb values into one dimensional FLTK output buffer
/*
this function is responisble for mapping rgb values from a given pixel at a two-dimensional location(row,col)
into the one-dimensional array buf.jump to the correct location in buf and assign r, g,b
since each pixel stores 3 bytes (rgb), each row will have a size of xPixels*3 bytes and each col will add another 3bytes.
writePixel(buf,xPixels,row,col,r,g,b);
*/
void writePixel(unsigned char* buf, int xPixels, int row, int col, unsigned char r, unsigned char g, unsigned char b)
{
  long int jumpToValue=(row * xPixels + col) * 3;
  buf[jumpToValue]= r;
  buf[jumpToValue+1]= g;
  buf[jumpToValue+2]= b;
}
///count the number of Mandelbrot iterations for a given point on the complex plane, used to determine pixel color
/*
Construct a complex number c from the given re and im
Construct a complex number z to accumulate each iteration.  Initialize it to (0,0)
Repeatedly calculate  z = z*z + c, until abs(z) is greater than 2.0 or the iterations have exceeded maxIterations
Return the number of iterations to the caller.
*/
int countIterations(double re, double im, int maxIterations)
{
  complex<double> c(re,im);
  complex<double> z(0,0);
  int i = 0;
  do {
    z = z*z +c;
    i++;
  } while(i<maxIterations && abs(z) <=2.0);
  return i;
}

/////*************
////ComplexPlane::
///Called repeatedly by graphics engine
///do not change buf here, just draw its current value
/*
We will make use of the FLTK library function fl_draw_image (Links to an external site.) to draw our images:
fl_draw_image(buf, 0, y_pixel_offset, xPixels, yPixels);
We will call this function with the following arguments:
One-dimensional array/pointer of unsigned chars
There are three bytes for each pixel, written as rgb values, aligned into a one-dimensional array.  The rows are written one after another.
Loading values into this array will be handled by a different function.
Assume it is loaded.
two ints for the (x,y) pixel coordinates of the upper left corner of the image
x offset will be 0, y will be shifted slightly down from the top of the window
two ints for width and height of the image, in pixel
draw_lines will be called automatically by the graphics engine every time the Window needs to be refreshed,
so we should not do any other computation in this function.
*/
void ComplexPlane::draw_lines() const
{
  fl_draw_image(buf,0,y_pixel_offset,xPixels,yPixels);
}

///this function is called in main when the complex plane changes
///for each pixel, map it to a point on the complex plane
///count the number of Mandelbrot iterations for that point
///assign its iteration count to a color
///use writePixel to write the color for that pixel to the output buffer
/*
This function will map each pixel to its corresponding coordinate on the complex plane, calculate the number of iterations that coordinate generates from the Mandelbrot Set, convert that number of iterations to an rgb color, and then write the rgb values into the output buffer.
The first thing to do is to calculate the size and location of the complex plane you are mapping to.
Assume the following member variables already have values in them.  They are given default values upon construction and can also be changed in main after the user interacts with the ZoomWindow:
center, the complex coordinate of the center of the complex plane.
The default ranges for the real and imaginary axes, reRange and imRange.
zoomLevel, which will multiply the default range values to be larger or smaller
Thus, the complex plane for which you will calculate the Mandelbrot set will be centered at center and have a width of reRange * zoomLevel and a height of imRange * zoomLevel.
Use mapRange to map each pixel to the complex plane as follows:

Each pixel must be mapped to a value on the complex plane, and then iterated to determine its place in the set.  This is very CPU intensive.  This code does not use multiple cores or the video card, so it is very easy for it to become bogged down and unresponsive.  To address this we will only calculate every fourth pixel.  This counter is stored in the variable pxResolution.
Use the number of iterations from countIteration to determine the color of the given pixel.  To do this, we will use the FLTK function Fl::get_color() (Links to an external site.) to give us an index mapped rgb value from 0 to 255.  The source code for how to call this is given below.  If the number of iterations reaches our value of maxIterations, or 255, we want our pixel to be colored black.  Thus, we will pass maxIterations - iterations into our color mapping function to achieve the desired result.
To put it all together, createBuffer will take on the following structure:
*/
void ComplexPlane::createBuffer()
{
    ///calculate the endpoints of the real and imaginary axes for mapping
    double re_left= center.real() - (reRange /2)*zoomLevel,
           re_right= center.real() + (reRange/2)*zoomLevel,
           im_bottom = center.imag() -(imRange /2)*zoomLevel,
           im_top = center.imag() + (imRange/2)*zoomLevel;

    for(int i = 0; i <= yPixels - pxResolution; i+=pxResolution)
    {
        for(int j = 0; j <= xPixels - pxResolution; j+=pxResolution)
        {
            ///map j to a real number = x axis
            //double mapRange(double n, double fromLow, double fromHigh, double toLow, double toHigh)
            //{return toLow+((double)n - fromLow)*(toHigh-toLow)/(fromHigh-fromLow);
            // center.real()- (reRange/2) * zoomLevel shifts the bottom left corner

            double re = mapRange(double(j),0,double(xPixels),re_left,re_right);
            ////////////Second try //////////
            //double re = mapRange(double(j),0.0,double(xPixels),re_bottom,re_top);

            ////////////first try ///////////
            //double re = mapRange(double(j),0,double(xPixels),center.real()-(reRange/2)*zoomLevel, reRange);   //reRange*zoomLevel incorrect!

            ///map i to an imaginary number = y axis

            double im = mapRange(double(i),double(yPixels),0.0,im_bottom, im_top);
            ////////////Second try //////////
            //double im = mapRange(double(i),double(yPixels),0.0,im_bottom,im_top);
            //////////First try////////////
            //double im = mapRange(double(i),double(yPixels),0,center.imag()-(imRange/2)*zoomLevel, imRange);

            ///call countIterations and save its return value in an int called iterations
            int iterations = countIterations(re,im, maxIterations);
            unsigned char r,g,b;
            Fl::get_color(maxIterations - iterations, r,g,b);
            for(int row = i; row < i + pxResolution; row++)
            {
                for(int col = j; col < j + pxResolution; col++)
                {
                    ///call writePixel for the given row, col
                    writePixel(buf,xPixels,row,col,r,g,b);
                }
            }
        }
    }
}
