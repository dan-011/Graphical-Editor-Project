//
//  ECAbstractConvexPolygon.h
//  

#ifndef ECAbstractConvexPolygon_h
#define ECAbstractConvexPolygon_h

#include <vector>
#include "ECLineSegment.h"
#include "ECAbstract2DShape.h"

// -----------------------------------------------------------------------------
// Convex polygon on 2D plane: interface class
// Note: we assume there is at least three nodes in the polygon (i.e., you don't
// need to deal with invalid inputs with fewer than three nodes)

class ECAbstractConvexPolygon: public ECAbstract2DShape
{
public:
    // Constructor for empty polygon
    ECAbstractConvexPolygon();
    
    // Consructor takes a list of nodes, which are the nodes of the polygon
    // ordered sequentially (either clockwise or counter clockwise
    ECAbstractConvexPolygon(const std::vector<EC2DPoint> &listNodes);
    
    // Test if the polygon is convex? Return false if not
    // NOTE: ALL OTHER METHODS OF THIS CLASS ASSUME THE POLYGON IS CONVEX
    virtual bool IsConvex() const = 0;
    
    // Test if the passed-in polygon is contained within this polygon
    // again, if the polygon (rhs) has vertex on the side of this polygon, it is allowed (considered to be contained)
    bool IsContaining(const ECAbstractConvexPolygon &rhs) const;
    
    // Test if two polygons intersect (i.e. has non-empty common area)
    bool IsIntersecting(const ECAbstractConvexPolygon &rhs) const;
    
    // add node (should add sequentially)
    void AddNode(const EC2DPoint &node);
    
    ECLineSegment GetLine(const int position) const;

    EC2DPoint GetNode(const int position) const;

    int NumLines() const;

    int NumberOfNodes() const;

    // Test if a point is inside the shape (if on the boundary, consider it is inside)
    virtual bool IsPointInside(const EC2DPoint &pt) const override;

    // find out the center of the shape and store in (xc,yc); round down to the closest integer
    virtual void GetCenter(double &xc, double &yc) const override; // TODO

    // Get bounding box (i.e. smallest rectangle contaiing the shape with sides parellel to axes) of the shape
    // the left-upper corner of the window is (0,0)
    virtual void GetBoundingBox( double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight ) const override;

private:
    std::vector<ECLineSegment> lineSegments;
    std::vector<EC2DPoint> listNodes;
    void SetLines(std::vector<ECLineSegment> &lines);
};


#endif /* ECAbstractConvexPolygon_h */
