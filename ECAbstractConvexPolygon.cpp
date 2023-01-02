//
//  ECAbstractConvexPolygon.h
//  

#include "ECAbstractConvexPolygon.h"
#include <iostream>

using namespace std;

#define NEGATIVE(a)((a) < 0)

// -----------------------------------------------------------------------------
// Convex polygon on 2D plane: interface class
ECAbstractConvexPolygon::ECAbstractConvexPolygon(){}
    
// Consructor takes a list of nodes, which are the nodes of the polygon
// ordered sequentially (either clockwise or counter clockwise
ECAbstractConvexPolygon::ECAbstractConvexPolygon(const std::vector<EC2DPoint> &listNodes): listNodes(listNodes){
    SetLines(lineSegments);
}

ECLineSegment ECAbstractConvexPolygon::GetLine(const int position) const{
    return lineSegments.at(position);
}


int ECAbstractConvexPolygon::NumberOfNodes() const{
    return listNodes.size();
}

// Test if a point is inside the polygon (if on the edge, consider it is inside)
bool ECAbstractConvexPolygon::IsPointInside(const EC2DPoint &pt) const{ // pi->pj : pi->pk 
    if(NumLines() == 0){
        return false;
    }
    bool samePoint = true;
    for (int i = 0; i < NumberOfNodes() - 1; i++) {
        if(GetNode(i).GetX() != GetNode(i + 1).GetX() || GetNode(i).GetY() != GetNode(i + 1).GetY()) {
            samePoint = false;
        }
    }
    if (samePoint && (pt.GetX() == GetNode(0).GetX() && pt.GetY() == GetNode(0).GetY())) return true;
    else if (samePoint && !(pt.GetX() == GetNode(0).GetX() && pt.GetY() == GetNode(0).GetY())) return false;
    for(ECLineSegment lineSegment : lineSegments){
        if(lineSegment.PointIntersect(pt)){
            return true;
        }
    }
    ECLineSegment firstSegment = lineSegments[0];
    EC2DPoint p1 = firstSegment.GetPoints().first;
    EC2DPoint p2 = firstSegment.GetPoints().second;

    bool isNegative = NEGATIVE(firstSegment.Direction(p1, p2, pt));

    for(ECLineSegment lineSegment : lineSegments){
        p1 = lineSegment.GetPoints().first;
        p2 = lineSegment.GetPoints().second;
        if(isNegative && !NEGATIVE(lineSegment.Direction(p1, p2, pt))){
            return false;
        }
        else if(!isNegative && NEGATIVE(lineSegment.Direction(p1, p2, pt))){
            return false;
        }
    }

    return true;
}
    
// Test if the passed-in polygon is contained within this polygon
// again, if the polygon (rhs) has vertex on the side of this polygon, it is allowed (considered to be contained)
bool ECAbstractConvexPolygon::IsContaining(const ECAbstractConvexPolygon &rhs) const{
    for(EC2DPoint point : rhs.listNodes){
        if(!IsPointInside(point)){
            return false;
        }
    }
    return true;
}
    
// Test if two polygons intersect (i.e. has non-empty common area)
bool ECAbstractConvexPolygon::IsIntersecting(const ECAbstractConvexPolygon &rhs) const{
    if(IsContaining(rhs) || rhs.IsContaining(*this)){
        return true;
    }

    for(ECLineSegment lineSegmentA : lineSegments){
        for(ECLineSegment lineSegmentB : rhs.lineSegments){
            if(lineSegmentA.IsIntersect(lineSegmentB)){
                return true;
            }
        }
    }

    return false;
}

void ECAbstractConvexPolygon::AddNode(const EC2DPoint &node){
    listNodes.push_back(node);
    SetLines(lineSegments);
}

void ECAbstractConvexPolygon::SetLines(vector<ECLineSegment> &lines){
    lines.clear();
    if(NumberOfNodes() > 2){
        EC2DPoint firstNode = listNodes[0];
        EC2DPoint lastNode = listNodes[NumberOfNodes() - 1];
        for(int i = 0; i < NumberOfNodes() - 1; i++){
            ECLineSegment line(listNodes[i], listNodes[i+1]);
            lines.push_back(line);
        }
        ECLineSegment endToStart(lastNode, firstNode);
        lines.push_back(endToStart);
    }
    else{
        for(int i = 0; i < NumberOfNodes() - 1; i++){
            ECLineSegment line(listNodes[i], listNodes[i+1]);
            lines.push_back(line);
        }
    }
}

int ECAbstractConvexPolygon::NumLines() const{
    return lineSegments.size();
}

EC2DPoint ECAbstractConvexPolygon::GetNode(const int position) const{
    return listNodes.at(position);
}

void ECAbstractConvexPolygon::GetBoundingBox( double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight ) const{
    if(NumberOfNodes() == 0) return;
    xUpperLeft = GetNode(0).GetX(); // lowest X value
    yUpperLeft = GetNode(0).GetY(); // highest y value
    xLowerRight = GetNode(0).GetX(); // highest x value
    yLowerRight = GetNode(0).GetY(); // lowest y value
    for(int i = 0; i < NumberOfNodes(); i++){
        double x = GetNode(i).GetX();
        double y = GetNode(i).GetY();
        if(x < xUpperLeft) xUpperLeft = x;
        else if(x > xLowerRight) xLowerRight = x;

        if(y < yUpperLeft) yUpperLeft = y;
        else if(y > yLowerRight) yLowerRight = y;
    }
}

void ECAbstractConvexPolygon::GetCenter(double &xc, double &yc) const{
    double xUpperLeft;
    double yUpperLeft;
    double xLowerRight;
    double yLowerRight;

    GetBoundingBox(xUpperLeft, yUpperLeft, xLowerRight, yLowerRight);
    xc = (xUpperLeft + xLowerRight)/2;
    yc = (yUpperLeft + yLowerRight)/2;
}