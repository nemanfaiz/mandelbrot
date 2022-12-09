#include "ZoomWindow.h"

void unitTests();

int main()
{
    unitTests();
    try
    {
        ZoomWindow win(Point(0,0),x_max(),y_max(),"Mandelbrot Set");
        ComplexPlane plane(complex<double>(0,0), 1.0, x_max(), y_max() - 100);
        win.attach(plane);
        plane.createBuffer();

        while(true)
        {
            win.wait_for_button();
            plane.setCenter(complex<double>(win.getCenter_r(), win.getCenter_i()));
            plane.setZoomLevel(win.getZoom());
            plane.createBuffer();
        }
    }
    catch(exception& e)
    {
        cout << "exception: " << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        cout << "Some exception\n";
        return 2;
    }
}

/********************       UNIT TESTS      *****************************************************************/
bool almostEqual(double a, double b, double eps = 0.0001)
{
    return fabs(a - b) < eps;
}

void unitTests()
{
    int score = 0;
    cout << "Testing ZoomWindow buttons..." << endl;
    string s = "Type 1.5 in Zoom Level, 2.6 in Center r, and 3.7 in Center i, then click next...";
    cout << s;
    ZoomWindow win(Point(0,0),x_max(),y_max(),"Unit Tester");
    Text t(Point(50,20), s);
    ComplexPlane plane(complex<double>(0,0), 1.0, x_max(), y_max() - 100);
    win.attach(t);
    win.attach(plane);
    plane.createBuffer();
    win.wait_for_button();
    plane.setCenter(complex<double>(win.getCenter_r(), win.getCenter_i()));
    plane.setZoomLevel(win.getZoom());
    plane.createBuffer();
    if(almostEqual(win.getZoom(), 1.5) && almostEqual(win.getCenter_r(), 2.6) && almostEqual(win.getCenter_i(), 3.7))
    {
        cout << " Passed. +3" << endl;
        score+=3;
    }
    else
    {
        cout << " Failed." << endl;
    }

    cout << "Testing mapRange...";
    if(almostEqual(mapRange(0.1, -1.0, 1.0, -500, 500), 50) &&
       almostEqual(mapRange(50, -500, 500, -1.0, 1.0), 0.1) &&
       almostEqual(mapRange(50, 500, -500, -1.0, 1.0), -0.1))
    {
        cout << " Passed. +1" << endl;
        score++;
    }
    else
    {
        cout << " Failed." << endl;
    }

    cout << "Testing writePixel...";
    unsigned char* buf = new unsigned char[360]; ///10 row x 12 cols x 3 (r,g,b)
    writePixel(buf, 12, 3, 4, 88, 111, 222);
    if(buf[(3 * 12  + 4) * 3] == 88 &&
       buf[(3 * 12  + 4) * 3 + 1] == 111 &&
       buf[(3 * 12  + 4) * 3 + 2] == 222)
    {
        cout << " Passed. +1" << endl;
        score++;
    }
    else
    {
        cout << " Failed." << endl;
    }

    cout << "Testing countIterations...";
    if(countIterations(0,0,255) == 255 &&
       countIterations(-0.7463, 0.1102, 255) == 83 &&
       countIterations(-0.7453, 0.1127, 255) == 74)
    {
        cout << " Passed. +1" << endl;
        score++;
    }
    else
    {
        cout << " Failed." << endl;
    }

    cout << "Score: " << score << "/" << 6 << endl;
    win.wait_for_button();
    win.detach(t);
    win.hide();
}
