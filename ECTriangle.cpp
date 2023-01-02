//
//  ECTriangle.cpp
//  

#include "ECTriangle.h"
#include <cmath>
using namespace std;

ECTriangle::ECTriangle(const EC2DPoint &p1, const EC2DPoint &p2, const EC2DPoint &p3): ECAbstractConvexPolygon({p1, p2, p3}){
}
    
// Test if the polygon is convex? Return false if not
bool ECTriangle::IsConvex() const{
    return true;
}
    
// Get area of the triangle
double ECTriangle::GetArea() const{
    const double a = GetLine(0).Length();
    const double b = GetLine(1).Length();
    const double c = GetLine(2).Length();

    double s = (a + b + c)/2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}