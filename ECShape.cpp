#include "ECShape.h"

//************************************************************************************************************
// ECShape
ECShape::~ECShape() {}
void ECShape::Move(const EC2DPoint& startPoint, const EC2DPoint& endPoint, int windowWidth, int windowHeight) {
	int xS = startPoint.GetX();
	int yS = startPoint.GetY();
	int xE = endPoint.GetX();
	int yE = endPoint.GetY();
	int xTransform = xE - xS;
	int yTransform = yE - yS;
	EC2DPoint p1 = GetDrawPoints().first;
	EC2DPoint p2 = GetDrawPoints().second;
	int x1 = p1.GetX();
	int y1 = p1.GetY();
	int x2 = p2.GetX();
	int y2 = p2.GetY();
	int rectWidth = abs(x2 - x1);
	int rectHeight = abs(y2 - y1);
	x1 += xTransform;
	x2 += xTransform;
	y1 += yTransform;
	y2 += yTransform;
	AdjustBounds(x1, y1, x2, y2, rectWidth, rectHeight, windowWidth, windowHeight);
	Resize(x1, y1, x2, y2);
}
void ECShape::Shift(int shiftX, int shiftY, int windowWidth, int windowHeight) {
	int xS = GetDrawPoints().first.GetX();
	int yS = GetDrawPoints().first.GetY();
	int xE = GetDrawPoints().second.GetX();
	int yE = GetDrawPoints().second.GetY();
	xS += shiftX;
	xE += shiftX;
	yS += shiftY;
	yE += shiftY;
	AdjustBounds(xS, yS, xE, yE, abs(xS - xE), abs(yS - yE), windowWidth, windowHeight);
	Resize(xS, yS, xE, yE);
}

std::pair<EC2DPoint, EC2DPoint> ECShape::GetBoundingBoxPoints() const {
	return boundingBox;
}

void ECShape::SetBoundingBox(const std::pair<EC2DPoint, EC2DPoint>& points) {
	boundingBox = points;
}

void ECShape::SetThickness(int t) {
	drawingContext.SetThickness(t);
}

int ECShape::GetThickness() const {
	return drawingContext.GetThickness();
}

void ECShape::SetColor(ECGVColor c) {
	drawingContext.SetColor(c);
}

ECGVColor ECShape::GetColor() const {
	return drawingContext.GetColor();
}

void ECShape::AdjustInnerBounds(int& c1, int& c2, int adjustSize) {
	if (c1 < 0) {
		c1 = 0;
		c2 = adjustSize;
	}
}

void ECShape::AdjustOuterBounds(int& c1, int& c2, int adjustSize, int upperBound) {
	if (c1 > upperBound) {
		c1 = upperBound;
		c2 = upperBound - adjustSize;
	}
}

void ECShape::AdjustBounds(int& x1, int& y1, int& x2, int& y2, int adjustXSize, int adjustYSize, int upperXBound, int lupperYBound) {
	AdjustInnerBounds(x1, x2, adjustXSize);
	AdjustInnerBounds(x2, x1, adjustXSize);
	AdjustInnerBounds(y1, y2, adjustYSize);
	AdjustInnerBounds(y2, y1, adjustYSize);
	AdjustOuterBounds(x1, x2, adjustXSize, upperXBound);
	AdjustOuterBounds(x2, x1, adjustXSize, upperXBound);
	AdjustOuterBounds(y1, y2, adjustYSize, lupperYBound);
	AdjustOuterBounds(y2, y1, adjustYSize, lupperYBound);
}

//************************************************************************************************************
// ECRectangularShape
ECRectangularShape::ECRectangularShape(int xS, int yS, int xE, int yE) {
	Resize(xS, yS, xE, yE);
}

ECRectangularShape::ECRectangularShape(const ECRectangularShape& rhs) {
	SetColor(rhs.GetColor());
	SetThickness(rhs.GetThickness());
	std::pair<EC2DPoint, EC2DPoint> drawPoints = rhs.GetDrawPoints();
	SetShape(drawPoints.first.GetX(), drawPoints.first.GetY(), drawPoints.second.GetX(), drawPoints.second.GetY());
	SetDrawPoints(drawPoints.first.GetX(), drawPoints.first.GetY(), drawPoints.second.GetX(), drawPoints.second.GetY());
}

ECRectangularShape:: ~ECRectangularShape() {}

ECShape& ECRectangularShape::operator=(const ECShape& rhs) {
	SetColor(rhs.GetColor());
	SetThickness(rhs.GetThickness());
	std::pair<EC2DPoint, EC2DPoint> drawPoints = rhs.GetDrawPoints();
	SetShape(drawPoints.first.GetX(), drawPoints.first.GetY(), drawPoints.second.GetX(), drawPoints.second.GetY());
	SetDrawPoints(drawPoints.first.GetX(), drawPoints.first.GetY(), drawPoints.second.GetX(), drawPoints.second.GetY());
	return *this;
}

void ECRectangularShape::Draw(ECGraphicViewImp& view) {
	view.DrawRectangle(GetBoundingBoxPoints().first.GetX(), GetBoundingBoxPoints().first.GetY(), GetBoundingBoxPoints().second.GetX(), GetBoundingBoxPoints().second.GetY(), GetThickness(), GetColor());
}

void ECRectangularShape::Resize(int xS, int yS, int xE, int yE) {
	SetDrawPoints(xS, yS, xE, yE);
	SetShape(xS, yS, xE, yE);
	double x1 = xS;
	double x2 = xE;
	double y1 = yS;
	double y2 = yE;
	rectangleShape.GetBoundingBox(x1, y1, x2, y2);
	EC2DPoint p1((int)x1, (int)y1);
	EC2DPoint p2((int)x2, (int)y2);
	SetBoundingBox(std::pair<EC2DPoint, EC2DPoint>(p1, p2));
}
void ECRectangularShape::SetShape(int xS, int yS, int xE, int yE) {
	std::vector<EC2DPoint> points = RectanglePoints(xS, yS, xE, yE);
	ECConvexPolygon poly(points);
	rectangleShape = poly;
}

void ECRectangularShape::SetDrawPoints(int xS, int yS, int xE, int yE) {
	EC2DPoint pS(xS, yS);
	EC2DPoint pE(xE, yE);
	drawPoints = std::pair<EC2DPoint, EC2DPoint>(pS, pE);
}

std::pair<EC2DPoint, EC2DPoint> ECRectangularShape::GetDrawPoints() const {
	return drawPoints;
}

bool ECRectangularShape::IsPointInside(const EC2DPoint& point) {
	return rectangleShape.IsPointInside(point);
}

EC2DPoint ECRectangularShape::GetCenterPoint() const {
	double x;
	double y;
	rectangleShape.GetCenter(x, y);
	EC2DPoint point(x, y);
	return point;
}

std::string ECRectangularShape::GetFileString() const {
	std::string res;
	res += "0 4 " + std::to_string((int)GetBoundingBoxPoints().first.GetX()) + ' ';
	res += std::to_string((int)GetBoundingBoxPoints().first.GetY()) + ' ';

	res += std::to_string((int)GetBoundingBoxPoints().first.GetX()) + ' ';
	res += std::to_string((int)GetBoundingBoxPoints().second.GetY()) + ' ';

	res += std::to_string((int)GetBoundingBoxPoints().second.GetX()) + ' ';
	res += std::to_string((int)GetBoundingBoxPoints().second.GetY()) + ' ';

	res += std::to_string((int)GetBoundingBoxPoints().second.GetX()) + ' ';
	res += std::to_string((int)GetBoundingBoxPoints().first.GetY()) + ' ';

	res += std::to_string((int)GetColor());
	res += '\n';
	return res;
}

std::vector<EC2DPoint> ECShape::RectanglePoints(int xS, int yS, int xE, int yE) {
	EC2DPoint p1(xS, yS);
	EC2DPoint p2(xE, yS);
	EC2DPoint p3(xE, yE);
	EC2DPoint p4(xS, yE);
	std::vector<EC2DPoint> points = { p1, p2, p3, p4 };
	return points;
}

void ECRectangularShape::GetBoundingBox(int& x1, int& y1, int& x2, int& y2) {
	x1 = GetBoundingBoxPoints().first.GetX();
	y1 = GetBoundingBoxPoints().first.GetY();
	x2 = GetBoundingBoxPoints().second.GetX();
	y2 = GetBoundingBoxPoints().second.GetY();
}

//************************************************************************************************************
// ECEllipseShape
ECEllipseShape::ECEllipseShape(int xS, int yS, int xE, int yE): ellipseShape(-1, -1, -1, -1) {
	Resize(xS, yS, xE, yE);

}
ECEllipseShape::ECEllipseShape(const ECEllipseShape& rhs): ellipseShape(-1, -1, -1, -1) {
	SetColor(rhs.GetColor());
	SetThickness(rhs.GetThickness());
	std::pair<EC2DPoint, EC2DPoint> drawPoints = rhs.GetDrawPoints();
	SetShape(drawPoints.first.GetX(), drawPoints.first.GetY(), drawPoints.second.GetX(), drawPoints.second.GetY());
	SetDrawPoints(drawPoints.first.GetX(), drawPoints.first.GetY(), drawPoints.second.GetX(), drawPoints.second.GetY());
}
ECEllipseShape::~ECEllipseShape() {}
ECShape& ECEllipseShape::operator=(const ECShape& rhs) {
	SetColor(rhs.GetColor());
	SetThickness(rhs.GetThickness());
	std::pair<EC2DPoint, EC2DPoint> drawPoints = rhs.GetDrawPoints();
	SetShape(drawPoints.first.GetX(), drawPoints.first.GetY(), drawPoints.second.GetX(), drawPoints.second.GetY());
	SetDrawPoints(drawPoints.first.GetX(), drawPoints.first.GetY(), drawPoints.second.GetX(), drawPoints.second.GetY());
	return *this;
}
void ECEllipseShape::Draw(ECGraphicViewImp& view) {
	double rx;
	double ry;
	GetRadii(rx, ry);
	view.DrawEllipse(GetCenterPoint().GetX(), GetCenterPoint().GetY(), rx, ry, GetThickness(), GetColor());
}
void ECEllipseShape::Resize(int xS, int yS, int xE, int yE) {
	SetDrawPoints(xS, yS, xE, yE);
	SetShape(xS, yS, xE, yE);
	double x1 = xS;
	double x2 = xE;
	double y1 = yS;
	double y2 = yE;
	ellipseShape.GetBoundingBox(x1, y1, x2, y2);
	EC2DPoint p1((int)x1, (int)y1);
	EC2DPoint p2((int)x2, (int)y2);
	SetBoundingBox(std::pair<EC2DPoint, EC2DPoint>(p1, p2));
}
void ECEllipseShape::SetShape(int xS, int yS, int xE, int yE) {
	int cX;
	int cY;
	double rX;
	double rY;
	EllipseParams(xS, yS, xE, yE, cX, cY, rX, rY);
	ellipseShape = ECEllipse(cX, cY, rX, rY);
}

void ECEllipseShape::GetBoundingBox(int& x1, int& y1, int& x2, int& y2) {
	x1 = GetBoundingBoxPoints().first.GetX();
	y1 = GetBoundingBoxPoints().first.GetY();
	x2 = GetBoundingBoxPoints().second.GetX();
	y2 = GetBoundingBoxPoints().second.GetY();
}

void ECEllipseShape::SetDrawPoints(int xS, int yS, int xE, int yE) {
	drawPoints = std::pair<EC2DPoint, EC2DPoint>(EC2DPoint(xS, yS), EC2DPoint(xE, yE));
}
std::pair<EC2DPoint, EC2DPoint> ECEllipseShape::GetDrawPoints() const {
	return drawPoints;
}
bool ECEllipseShape::IsPointInside(const EC2DPoint& point) {
	return ellipseShape.IsPointInside(point);
}

EC2DPoint ECEllipseShape::GetCenterPoint() const {
	double x;
	double y;
	ellipseShape.GetCenter(x, y);
	EC2DPoint center((int)x, (int)y);
	return center;
}



std::string ECEllipseShape::GetFileString() const {
	std::string res;
	res += "1 " + std::to_string((int)GetCenterPoint().GetX()) + ' ';
	res += std::to_string((int)GetCenterPoint().GetY()) + ' ';
	int xRad = abs(GetBoundingBoxPoints().first.GetX() - GetBoundingBoxPoints().second.GetX()) / 2;
	int yRad = abs(GetBoundingBoxPoints().first.GetY() - GetBoundingBoxPoints().second.GetY()) / 2;
	res += std::to_string(xRad) + ' ';
	res += std::to_string(yRad) + ' ';
	res += std::to_string((int)GetColor());
	res += '\n';
	return res;
}

void ECEllipseShape::GetRadii(double& rX, double& rY) const {
	int xS = drawPoints.first.GetX();
	int xE = drawPoints.second.GetX();
	int yS = drawPoints.first.GetY();
	int yE = drawPoints.second.GetY();
	rX = abs(xS - xE) / 2;
	rY = abs(yS - yE) / 2;
}
void ECEllipseShape::EllipseParams(int xS, int yS, int xE, int yE, int& x, int& y, double& radiusx, double& radiusy) {
	GetRadii(radiusx, radiusy);
	std::vector<EC2DPoint> points(RectanglePoints(xS, yS, xE, yE));
	ECConvexPolygon rectangle(points);
	double cX;
	double cY;
	rectangle.GetCenter(cX, cY);
	x = (int)cX;
	y = (int)cY;
}

//************************************************************************************************************
// ECFilledRectangularShape
ECFilledRectangularShape::ECFilledRectangularShape(int xS, int yS, int xE, int yE) : ECRectangularShape(xS, yS, xE, yE) {}
ECFilledRectangularShape::~ECFilledRectangularShape() {}
void ECFilledRectangularShape::Draw(ECGraphicViewImp& view) {
	/*int xS = GetDrawPoints().first.GetX();
	int yS = GetDrawPoints().first.GetY();
	int xE = GetDrawPoints().second.GetX();
	int yE = GetDrawPoints().second.GetY();
	AdjustBounds(xS, yS, xE, yE, abs(xS - xE), abs(yS - yE), view.GetWith(), view.GetHeight());
	Resize(xS, yS, xE, yE);*/
	view.DrawFilledRectangle(GetBoundingBoxPoints().first.GetX(), GetBoundingBoxPoints().first.GetY(), GetBoundingBoxPoints().second.GetX(), GetBoundingBoxPoints().second.GetY(), GetColor());
}

std::string ECFilledRectangularShape::GetFileString() const {
	std::string res = ECRectangularShape::GetFileString();
	res[0] = '2';
	return res;
}

//************************************************************************************************************
// ECFilledEllipseShape
ECFilledEllipseShape::ECFilledEllipseShape(int xS, int yS, int xE, int yE) : ECEllipseShape(xS, yS, xE, yE) {}
ECFilledEllipseShape::~ECFilledEllipseShape() {}
void ECFilledEllipseShape::Draw(ECGraphicViewImp& view) {
	double rx;
	double ry;
	GetRadii(rx, ry);
	view.DrawFilledEllipse(GetCenterPoint().GetX(), GetCenterPoint().GetY(), rx, ry, GetColor());
}

std::string ECFilledEllipseShape::GetFileString() const {
	std::string res = ECEllipseShape::GetFileString();
	res[0] = '3';
	return res;
}

//************************************************************************************************************
// ECCompositeShape
ECCompositeShape::ECCompositeShape() {}
ECCompositeShape::~ECCompositeShape() {
	for (auto shape : shapeCollection) {
		if (shape != NULL) {
			delete shape;
		}
	}
}
ECShape& ECCompositeShape::operator=(const ECShape& rhs) { // DO SOMETHING WITH THIS
	for (int i = 0; i < rhs.GetNumShapes(); i++) {
		AddChild(rhs.GetShapeAt(i));
		AddLocation(rhs.GetLocationAt(i));
	}
	return *this;
}

void ECCompositeShape::AddChild(ECShape* shape) {
	shapeCollection.push_back(shape);
	int x1;
	int y1;
	int x2;
	int y2;
	GetBoundingBox(x1, y1, x2, y2);
}

ECShape* ECCompositeShape::RemoveChild(int index) {
	ECShape* ret = shapeCollection.at(index);
	shapeCollection.at(index) = NULL;
	return ret;
}

void ECCompositeShape::Draw(ECGraphicViewImp& view) {
	for (auto shape : shapeCollection) {
		if (shape == NULL) continue;
		shape->Draw(view);
	}
}

void ECCompositeShape::Shift(int shiftX, int shiftY, int windowWidth, int windowHeight) {
	int x1;
	int y1;
	int x2;
	int y2;
	GetBoundingBox(x1, y1, x2, y2);
	if ((x1 <= 0 && shiftX < 0) || (x2 >= windowWidth && shiftX > 0)) {
		shiftX = 0;
	}
	if ((y1 <= 0 && shiftY < 0) || (y2 >= windowHeight && shiftY > 0)) {
		shiftY = 0;
	}
	for (auto shape : shapeCollection) {
		if (shape == NULL) continue;
		shape->Shift(shiftX, shiftY, windowWidth, windowHeight);
	}
}

EC2DPoint ECCompositeShape::GetCenterPoint() const {
	int x1 = GetBoundingBoxPoints().first.GetX();
	int y1 = GetBoundingBoxPoints().first.GetY();
	int x2 = GetBoundingBoxPoints().second.GetX();
	int y2 = GetBoundingBoxPoints().second.GetY();
	EC2DPoint p1(x1, y1);
	EC2DPoint p2(x2, y1);
	EC2DPoint p3(x2, y2);
	EC2DPoint p4(x1, y2);
	std::vector<EC2DPoint> points = { p1, p2, p3, p4 };
	ECConvexPolygon poly(points);
	double cx;
	double cy;
	poly.GetCenter(cx, cy);
	return EC2DPoint((int)cx, (int)cy);
}


void ECCompositeShape:: Move(const EC2DPoint& startPoint, const EC2DPoint& endPoint, int windowWidth, int windowHeight) {
	int x1;
	int y1;
	int x2;
	int y2;
	GetBoundingBox(x1, y1, x2, y2);
	EC2DPoint movePoint = endPoint;
	if ((x1 <= 0 && endPoint.GetX() - startPoint.GetX() < 0) || (x2 >= windowWidth && endPoint.GetX() - startPoint.GetX() > 0)) {
		movePoint = EC2DPoint(startPoint.GetX(), movePoint.GetY());
	}
	if ((y1 <= 0 && endPoint.GetY() - startPoint.GetY() < 0) || (y2 >= windowHeight && endPoint.GetY() - startPoint.GetY() > 0)) {
		movePoint = EC2DPoint(movePoint.GetX(), startPoint.GetY());
	}
	for (auto shape : shapeCollection) {
		if (shape == NULL) continue;
		shape->Move(startPoint, movePoint, windowWidth, windowHeight);
	}
}

bool ECCompositeShape::IsPointInside(const EC2DPoint& point) {
	for (auto shape : shapeCollection) {
		if (shape == NULL) continue;
		if (shape->IsPointInside(point)) {
			return true;
		}
	}
	return false;
}

void ECCompositeShape::SetThickness(int t) {
	for (auto shape : shapeCollection) {
		if (shape == NULL) continue;
		shape->SetThickness(t);
	}
}
int ECCompositeShape::GetThickness() const {
	if (shapeCollection.size() == 0) return -1;
	int i = 0;
	while (shapeCollection.at(i) == NULL) i++;
	return shapeCollection.at(i)->GetThickness(); // assuming they all have the same thickness
}
void ECCompositeShape::SetColor(ECGVColor c) {
	for (auto shape : shapeCollection) {
		if (shape == NULL) continue;
		shape->SetColor(c);
	}
}
ECGVColor ECCompositeShape::GetColor() const {
	if (shapeCollection.size() == 0) return ECGV_NONE;
	int i = 0;
	while (shapeCollection.at(i) == NULL) i++;
	return shapeCollection.at(i)->GetColor(); // assuming they all have the same color
}

std::string ECCompositeShape::GetFileString() const {
	std::string res;
	res += "4 ";
	res += std::to_string(GetNumShapes()) + '\n';
	for (auto shape : shapeCollection) {
		if (shape == NULL) continue;
		res += shape->GetFileString();
	}
	return res;
}

void ECCompositeShape::GetBoundingBox(int& x1, int& y1, int& x2, int& y2) {
	if (shapeCollection.size() == 0) return;
	int i = 0;
	while (shapeCollection.at(i) == NULL) i++;
	shapeCollection.at(i)->GetBoundingBox(x1, y1, x2, y2);
	for (auto shape : shapeCollection) {
		int cxS;
		int cyS;
		int cxE;
		int cyE;
		if (shape == NULL) continue;
		shape->GetBoundingBox(cxS, cyS, cxE, cyE);
		if (cxS < x1) x1 = cxS;
		if (cyS < y1) y1 = cyS;
		if (cxE > x2) x2 = cxE;
		if (cyE > y2) y2 = cyE;
	}
	EC2DPoint p1(x1, y1);
	EC2DPoint p3(x2, y2);
	SetBoundingBox(std::pair<EC2DPoint, EC2DPoint>(p1, p3));
}

bool ECCompositeShape::Contains(ECShape* shape) const {
	return find(shapeCollection.begin(), shapeCollection.end(), shape) != shapeCollection.end();
}

void ECCompositeShape::ClearShapes() {
	shapeCollection.clear();
}

void ECCompositeShape::ClearLocations() {
	locations.clear();
}

ECShape* ECCompositeShape::GetShapeAt(int index) const {
	return shapeCollection.at(index);
}

int ECCompositeShape::GetNumShapes() const {
	return shapeCollection.size();
}

int ECCompositeShape::GetLocationAt(int index) const {
	return locations.at(index);
}

int ECCompositeShape::GetNumLocations() const {
	return locations.size();
}

void ECCompositeShape::AddChild(ECShape* shape, int location) {
	shapeCollection.push_back(shape);
	locations.push_back(location);
}

void ECCompositeShape::AddLocation(int location) {
	locations.push_back(location);
}