#ifndef COMPLEXPLANE_H_INCLUDED
#define COMPLEXPLANE_H_INCLUDED

#include <complex>
#include "Simple_window.h"

///helper functions to be unit tested
///map from pixels to complex plane
double mapRange(double n, double fromLow, double fromHigh, double toLow, double toHigh);
///write rgb values into one dimensional FLTK output buffer
void writePixel(unsigned char* buf, int xPixels, int row, int col, unsigned char r, unsigned char g, unsigned char b);
///count the number of Mandelbrot iterations for a given point on the complex plane, used to determine pixel color
int countIterations(double re, double im, int maxIterations);

struct ComplexPlane : Shape
{
    ///Allocate memory for the output buffer and assign default plane size
    ComplexPlane(complex<double> _center, double _zoomLevel, int _xPixels, int _yPixels)
    : center(_center), zoomLevel(_zoomLevel), xPixels(_xPixels), yPixels(_yPixels),
        imRange(4), reRange(4 * (1.0 * xPixels / yPixels))
    {
        buf = new unsigned char[xPixels * yPixels * 3];
    }

    ///Called repeatedly by graphics engine
    ///do not change buf here, just draw its current value
    void draw_lines() const;

    ///Set the complex plane center and size, called in main with values obtained from ZoomWindow
    void setZoomLevel(double _zoomLevel){zoomLevel = _zoomLevel;}
    void setCenter(complex<double> _center){center = _center;}

    ///this function is called in main when the complex plane changes
    ///for each pixel, map it to a point on the complex plane
    ///count the number of Mandelbrot iterations for that point
    ///assign its iteration count to a color
    ///use writePixel to write the color for that pixel to the output buffer
    void createBuffer();

    private:

        const int y_pixel_offset = 40;  ///offset from the top of the screen to draw the set
        const int maxIterations = 255;  ///used to calculate set values and determine color
        const double pxResolution = 4;  ///Resolution multiplier to speed calculation
        unsigned char* buf;             ///pixel rgb values to be drawn by the engine
        complex<double> center;         ///center of complex plane
        double zoomLevel;               ///multiplier of the default range: zoomLevel*(reRange), zoomLevel*(imRange)
        const int xPixels;              ///pixel width of the plane display
        const int yPixels;              ///pixel height of the plane display
        const double imRange;           ///default plane height.  Do not change this outside of the constructor
        const double reRange;           ///default plane width.  Do not change this outside of the constructor
};

#endif // COMPLEXPLANE_H_INCLUDED
