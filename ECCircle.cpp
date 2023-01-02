#include "ECCircle.h"
#include <cmath>
using namespace std;

//*************************************************************************************
// Circle

// (x,y): the center of circle, and radius
ECCircle::ECCircle(double x, double y, double radius): cx(x), cy(y), r(radius){}

// Get bounding box (i.e. smallest rectangle contaiing the shape with sides parellel to axes) of the shape
// the left-upper corner of the window is (0,0)
void ECCircle::GetBoundingBox(double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight) const{
    xUpperLeft = cx - r;
    xLowerRight = cx + r;
    yUpperLeft = cy - r;
    yLowerRight = cy + r;
}

// is the shape intersecting with point (px, py)
bool ECCircle::IsPointInside(const EC2DPoint &pt) const{
    EC2DPoint center(cx, cy);
    ECLineSegment line(pt, center);
    double dist = line.Length();
    if(dist < r || fabs(r - dist) < .00000001) return true;
    else return false;
}

double ECCircle::GetArea() const{
    return PI * r * r;
}
void ECCircle::GetCenter(double &xc, double &yc) const{
    xc = cx;
    yc = cy;
}


//*************************************************************************************
// Ellipse

// (x,y): the center of ellipse, and radiu along x and y coordinate
ECEllipse::ECEllipse(double x, double y, double radiusx, double radiusy): cx(x), cy(y), rx(radiusx), ry(radiusy){}

// Get bounding box (i.e. smallest rectangle contaiing the shape with sides parellel to axes) of the shape
// the left-upper corner of the window is (0,0)
void ECEllipse::GetBoundingBox(double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight) const{
    xUpperLeft = cx - rx;
    yUpperLeft = cy - ry;
    xLowerRight = cx + rx;
    yLowerRight = cy + ry;
}

// is the ellipse intersecting with point (px, py)
bool ECEllipse::IsPointInside(const EC2DPoint &pt) const{
    double x = pt.GetX();
    double y = pt.GetY();
    return ((((x - cx)*(x - cx))/(rx*rx)) + (((y - cy)*(y - cy))/(ry*ry))) <= 1;
}

double ECEllipse::GetArea() const{
    return PI * rx * ry;
}
void ECEllipse::GetCenter(double &xc, double &yc) const{
    xc = cx;
    yc = cy;
}