#ifndef ZOOMWINDOW_H_INCLUDED
#define ZOOMWINDOW_H_INCLUDED

#include "ComplexPlane.h"
#include "Simple_window.h"


struct ZoomWindow : Simple_window
{
    ZoomWindow(Point xy, int w, int h, const string& title);

    const double& getCenter_r() const{return center_r;}
    const double& getCenter_i() const{return center_i;}
    const double& getZoom() const{return zoom;}
    bool wait_for_button();

    private:

        double center_r, center_i, zoom;

        // Widgets:
        In_box next_i;
        In_box next_r;
        In_box next_zoom;
};


#endif // ZOOMWINDOW_H_INCLUDED
