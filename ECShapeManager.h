#ifndef __ECSHAPEMANAGER_H
#define __ECSHAPEMANAGER_H

#include "ECAbstract2DShape.h"
#include "ECAbstractConvexPolygon.h"
#include "ECConvexPolygon.h"
#include "ECShape.h"
#include <vector>

class ECAbstractShapeFactory {
public:
	virtual ~ECAbstractShapeFactory() {}
	virtual ECShape* CreateShape(int xS, int yS, int xE, int yE) = 0;
};

class ECRectangleFactory : public ECAbstractShapeFactory {
public:
	virtual ~ECRectangleFactory() {}
	virtual ECShape* CreateShape(int xS, int yS, int xE, int yE) override;
};

class ECEllipseFactory : public ECAbstractShapeFactory {
public:
	virtual ~ECEllipseFactory() {}
	virtual ECShape* CreateShape(int xS, int yS, int xE, int yE) override;
};

class ECFilledRectangleFactory : public ECAbstractShapeFactory {
public:
	virtual ~ECFilledRectangleFactory() {}
	virtual ECShape* CreateShape(int xS, int yS, int xE, int yE) override;
};

class ECFilledEllipseFactory : public ECAbstractShapeFactory {
public:
	virtual ~ECFilledEllipseFactory() {}
	virtual ECShape* CreateShape(int xS, int yS, int xE, int yE) override;
};

class ECShapeManager {
public:
	ECShapeManager();
	~ECShapeManager();
	ECShape* GenerateSelectedShapeType(int xS, int yS, int xE, int yE);
	void ChangeSelectedShape(ECAbstractShapeFactory* fact);
	ECAbstractShapeFactory* GetSelectedShape() const;
	void ToggleShapeType();
	void TeggleFilledShape();
private:
	ECAbstractShapeFactory* selectedShapeFactory;
	std::vector<std::vector<ECAbstractShapeFactory*>> factories;
	int row;
	int col;
};
#endif