#ifndef EC_ABSTRACT_2D_SHAPE_H
#define EC_ABSTRACT_2D_SHAPE_H

#include <vector>
#include "ECLineSegment.h"


// Abstract class for shape
class ECAbstract2DShape
{
public:
    virtual ~ECAbstract2DShape() {}
    // Get bounding box (i.e. smallest rectangle contaiing the shape with sides parellel to axes) of the shape
    // the left-upper corner of the window is (0,0)
    virtual void GetBoundingBox( double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight ) const = 0;
    
    // Test if a point is inside the shape (if on the boundary, consider it is inside)
    virtual bool IsPointInside(const EC2DPoint &pt) const = 0;
    
    // return the area of the shape
    virtual double GetArea() const = 0;
    
    // find out the center of the shape and store in (xc,yc); round down to the closest integer
    virtual void GetCenter(double &xc, double &yc) const = 0;
};

#endif
