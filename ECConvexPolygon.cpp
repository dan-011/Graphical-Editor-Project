//
//  ECConvexPolygon.cpp
//  

#include "ECConvexPolygon.h"
#include "ECTriangle.h"

#define CLOCKWISE(a)((a) > 0)
#define COUNTERCLOCKWISE(a)((a) < 0)

// -----------------------------------------------------------------------------
// Convex polygon on 2D plane: implementing polygon for non-triangles
ECConvexPolygon::ECConvexPolygon(const std::vector<EC2DPoint> &listNodes): ECAbstractConvexPolygon(listNodes){
}
    
// Test if the polygon is convex? Return false if not
bool ECConvexPolygon::IsConvex() const{
    for(int i = 0; i < NumLines(); i++){
        ECLineSegment line = GetLine(i);
        bool hasClockwisePoints = false;
        bool hasCounterClockwisePoints = false;
        for(int j = 0; j < NumberOfNodes(); j++){
            EC2DPoint pC = GetNode(j);
            if(line.OnSegment(pC)){
                continue;
            }
            else{
                double dir = line.Direction(pC);
                if(CLOCKWISE(dir)){
                    hasClockwisePoints = true;
                }
                if(COUNTERCLOCKWISE(dir)){
                    hasCounterClockwisePoints = true;
                }
            }
        }
        if(hasClockwisePoints && hasCounterClockwisePoints){
            return false;
        }
    }
    return true;
}
    
// Calculate total area of the polygon (you can assume it is indeed convex)
double ECConvexPolygon::GetArea() const{
    if(NumLines() < 3) return 0;
    if(NumLines() == 3){
        EC2DPoint p1 = GetNode(0);
        EC2DPoint p2 = GetNode(1);
        EC2DPoint p3 = GetNode(2);
        ECTriangle triangle(p1, p2, p3);
        return triangle.GetArea();
    }
    else{
        int numLines = NumLines();
        int middle = numLines/2;
        std::vector<EC2DPoint> v1;
        std::vector<EC2DPoint> v2;
        v1.push_back(GetNode(0));
        v2.push_back(GetNode(0));
        for(int i = 0; i < NumLines(); i++){
            if(i < middle){
                v1.push_back(GetLine(i).GetPoints().second);
            }
            else{
                v2.push_back(GetLine(i).GetPoints().first);
            }
        }
        ECConvexPolygon poly1(v1);
        ECConvexPolygon poly2(v2);

        return poly1.GetArea() + poly2.GetArea();
    }
}
