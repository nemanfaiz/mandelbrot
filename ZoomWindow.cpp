#include"ZoomWindow.h"
//
//(-.55110001,-.6279205110)
//(-1.401155,0)
//(-0.1528,1.03797)
//(-0.77568377,0.13646737) THIS IS THE COOOLEST
//(-1.54368901269109,0)

/////
/////.0004,.33833,.4564333
/////1.5,-1.401155,0
///
/*
Construct the three In_box members in an intialization list and then attach them, as you have done in the lab.  Position them to be in line with the next button at the top of the window.
Initialize center_r to 0, center_i to 0, and zoom to 1.0.
*/
ZoomWindow::ZoomWindow(Point xy, int w, int h, const string& title):Simple_window (xy,w,h,title),
  next_i(Point(x_max()-150,0),70,20,"Center i: "),
  next_r(Point(x_max()-350,0),70,20, "Center r: "),
  next_zoom(Point(x_max()-550,0),70,20, "Zoom Level: ")
{
attach(next_i);
attach(next_r);
attach(next_zoom);

center_i = 0;
center_r = 0;
zoom = 1.0;
}


/*
This function will take advantage of the parent Simple_window class's functionality
First, call Simple_window::wait_for_button()
This will wait for the callback event from the user as it normally does
You don't need to do anything with its boolean return value
When it returns, extract the values for center_r, center_i, and zoom from the In_boxes.
Using an istringstream is probably the easiest way to do this.
Don't forget to call .clear() on the stream in between reads in order to clear its EOF state.
*/
bool ZoomWindow::wait_for_button()
{
  Simple_window::wait_for_button();
  string input = next_i.get_string();
  istringstream iss{input};
  iss >> center_i;
  iss.clear();
  iss.str("");

  input = next_r.get_string();
  istringstream iss2{input};
  iss2 >> center_r;
  iss2.clear();
  iss2.str("");

  input = next_zoom.get_string();
  istringstream iss3{input};
  //input = zoom;
  iss3 >> zoom;
  iss3.clear();
  iss3.str("");

//////First Try/////////
  //cout << center_i << endl;
  //input = next_r.get_string();
  //istringstream iss (input);
  //iss >> center_r;
  //iss.clear();
  //iss.str("");

  //input = next_zoom.get_string();
  //istringstream iss (input);
  //iss >> next_zoom;
  //iss.clear();
  //iss.str("");

  //iss >> zoom;
  //iss.clear();

  //cout << center_i << endl;

  //cout << center_r << endl;
  //cout << zoom << endl;

  return true;

}




















/* wait_for_button

  iss >> center_r;
  iss.clear();
  iss >> zoom;
  iss.clear();

  cout << center_i << endl;

cout << center_r << endl;
cout << zoom << endl;
*/
