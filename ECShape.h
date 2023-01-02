#ifndef __ECSHAPE_H
#define __ECSHAPE_H

#include "ECAbstract2DShape.h"
#include "ECConvexPolygon.h"
#include "ECGraphicViewImp.h"
#include "ECCircle.h"
#include <vector>

class ECShape {
public:
	virtual ~ECShape();
	virtual ECShape& operator=(const ECShape& rhs) = 0;
	virtual void Draw(ECGraphicViewImp& view) = 0;
	virtual void Shift(int shiftX, int shiftY, int windowWidth, int windowHeight);
	virtual void Resize(int xS, int yS, int xE, int yE) = 0;
	virtual void SetShape(int xS, int yS, int xE, int yE) = 0;
	virtual void Move(const EC2DPoint& startPoint, const EC2DPoint& endPoint, int windowWidth, int windowHeight);
	virtual bool IsPointInside(const EC2DPoint& point) = 0;
	virtual EC2DPoint GetCenterPoint() const = 0;
	virtual void SetDrawPoints(int xS, int yS, int xE, int yE) = 0;
	virtual std::pair<EC2DPoint, EC2DPoint> GetDrawPoints() const = 0;
	virtual void SetThickness(int t);
	virtual int GetThickness() const;
	virtual void SetColor(ECGVColor c);
	virtual ECGVColor GetColor() const;
	virtual std::string GetFileString() const = 0;
	virtual void GetBoundingBox(int& x1, int& y1, int& x2, int& y2) = 0;
	virtual std::pair<EC2DPoint, EC2DPoint> GetBoundingBoxPoints() const;
	virtual void SetBoundingBox(const std::pair<EC2DPoint, EC2DPoint>& points);
	
	// Default behaviors overridden by composite shapes
	virtual void AddChild(ECShape* shape) {}
	virtual void AddChild(ECShape* shape, int location) {}
	virtual ECShape* RemoveChild(int index) { return NULL; }
	virtual ECShape* GetShapeAt(int index) const { return NULL; }
	virtual void ClearShapes() {}
	virtual void ClearLocations() {}
	virtual int GetNumShapes() const { return 1; }
	virtual int GetLocationAt(int index) const { return -1; }
	virtual void AddLocation(int location) {}
	virtual int GetNumLocations() const { return -1; }


protected:
	std::vector<EC2DPoint> RectanglePoints(int xS, int yS, int xE, int yE);
	virtual void AdjustBounds(int &x1, int& y1, int& x2, int& y2, int adjustXSize, int adjustYSize, int upperXBound, int lupperYBound);
	virtual void AdjustInnerBounds(int& c1, int& c2, int adjustSize);
	virtual void AdjustOuterBounds(int& c1, int& c2, int adjustSize, int upperBound);

private:
	ECDrawiingContext drawingContext;
	std::pair<EC2DPoint, EC2DPoint> boundingBox;
};

class ECRectangularShape : public ECShape {
public:
	ECRectangularShape(int xS, int yS, int xE, int yE);
	ECRectangularShape(const ECRectangularShape& rhs);
	virtual ~ECRectangularShape();
	virtual ECShape& operator=(const ECShape& rhs) override;
	virtual void Draw(ECGraphicViewImp& view) override;
	virtual void Resize(int xS, int yS, int xE, int yE) override;
	virtual void SetShape(int xS, int yS, int xE, int yE) override;
	virtual void SetDrawPoints(int xS, int yS, int xE, int yE);
	virtual std::pair<EC2DPoint, EC2DPoint> GetDrawPoints() const;
	virtual bool IsPointInside(const EC2DPoint& point) override;
	virtual EC2DPoint GetCenterPoint() const override;
	virtual std::string GetFileString() const override;
	virtual void GetBoundingBox(int& x1, int& y1, int& x2, int& y2) override;

private:
	std::pair<EC2DPoint, EC2DPoint> drawPoints;
	ECConvexPolygon rectangleShape;
};

class ECEllipseShape : public ECShape {
public:
	ECEllipseShape(int xS, int yS, int xE, int yE);
	ECEllipseShape(const ECEllipseShape& rhs);
	virtual ~ECEllipseShape();
	virtual ECShape& operator=(const ECShape& rhs) override;
	virtual void Draw(ECGraphicViewImp& view) override;
	virtual void Resize(int xS, int yS, int xE, int yE) override;
	virtual void SetShape(int xS, int yS, int xE, int yE) override;
	virtual void SetDrawPoints(int xS, int yS, int xE, int yE);
	virtual std::pair<EC2DPoint, EC2DPoint> GetDrawPoints() const;
	virtual bool IsPointInside(const EC2DPoint& point) override;
	virtual EC2DPoint GetCenterPoint() const override;
	virtual std::string GetFileString() const override;
	virtual void GetBoundingBox(int& x1, int& y1, int& x2, int& y2) override;

protected:
	void GetRadii(double& rX, double& rY) const;
	void EllipseParams(int xS, int yS, int xE, int yE, int& x, int& y, double& radiusx, double& radiusy);

private:
	std::pair<EC2DPoint, EC2DPoint> drawPoints;
	ECEllipse ellipseShape;
};

class ECFilledRectangularShape : public ECRectangularShape {
public:
	ECFilledRectangularShape(int xS, int yS, int xE, int yE);
	~ECFilledRectangularShape();
	virtual void Draw(ECGraphicViewImp& view) override;
	virtual std::string GetFileString() const override;
};

class ECFilledEllipseShape : public ECEllipseShape {
public:
	ECFilledEllipseShape(int xS, int yS, int xE, int yE);
	~ECFilledEllipseShape();
	virtual void Draw(ECGraphicViewImp& view) override;
	virtual std::string GetFileString() const override;
};

class ECCompositeShape : public ECShape {
public:
	ECCompositeShape();
	virtual ~ECCompositeShape();
	virtual void AddChild(ECShape* shape) override;
	virtual ECShape* RemoveChild(int index) override;
	virtual ECShape& operator=(const ECShape& rhs) override;
	virtual void Draw(ECGraphicViewImp& view) override;
	virtual void Shift(int shiftX, int shiftY, int windowWidth, int windowHeight) override;
	virtual void Move(const EC2DPoint& startPoint, const EC2DPoint& endPoint, int windowWidth, int windowHeight) override;
	virtual void Resize(int xS, int yS, int xE, int yE) override {}
	virtual void SetShape(int xS, int yS, int xE, int yE) override {}
	virtual void SetDrawPoints(int xS, int yS, int xE, int yE) override {}
	virtual std::pair<EC2DPoint, EC2DPoint> GetDrawPoints() const override { return std::pair<EC2DPoint, EC2DPoint>(EC2DPoint(-1, -1), EC2DPoint(-1, -1)); }
	virtual bool IsPointInside(const EC2DPoint& point) override;
	virtual EC2DPoint GetCenterPoint() const override;
	virtual void SetThickness(int t) override;
	virtual int GetThickness() const override;
	virtual void SetColor(ECGVColor c) override;
	virtual ECGVColor GetColor() const override;
	virtual std::string GetFileString() const override;
	virtual void GetBoundingBox(int& x1, int& y1, int& x2, int& y2) override;
	virtual void ClearShapes() override;
	virtual void ClearLocations() override;
	bool Contains(ECShape* shape) const;
	virtual ECShape* GetShapeAt(int index) const override;
	virtual int GetNumShapes() const override;
	virtual int GetLocationAt(int index) const override;
	virtual void AddLocation(int location) override;
	virtual void AddChild(ECShape* shape, int location) override;
	virtual int GetNumLocations() const override;


private:
	std::vector<ECShape*> shapeCollection;
	std::vector<int> locations;
};
#endif