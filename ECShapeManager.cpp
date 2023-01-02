#include "ECShapeManager.h"

//************************************************************************************************************
// ECRectangleFactory
ECShape* ECRectangleFactory::CreateShape(int xS, int yS, int xE, int yE) {
	return new ECRectangularShape(xS, yS, xE, yE);
}

//************************************************************************************************************
// ECEllipseFactory
ECShape* ECEllipseFactory::CreateShape(int xS, int yS, int xE, int yE) {
	return new ECEllipseShape(xS, yS, xE, yE);
}

//************************************************************************************************************
// ECFilledRectangleFactory
ECShape* ECFilledRectangleFactory::ECFilledRectangleFactory::CreateShape(int xS, int yS, int xE, int yE) {
	return new ECFilledRectangularShape(xS, yS, xE, yE);
}

//************************************************************************************************************
// ECFilledEllipseFactory
ECShape* ECFilledEllipseFactory::CreateShape(int xS, int yS, int xE, int yE) {
	return new ECFilledEllipseShape(xS, yS, xE, yE);
}

//************************************************************************************************************
// ECShapeManager
ECShapeManager::ECShapeManager() : row(0), col(0), selectedShapeFactory(NULL) {
	std::vector<ECAbstractShapeFactory*> hollowShapes;
	hollowShapes.push_back(new ECRectangleFactory);
	hollowShapes.push_back(new ECEllipseFactory);
	std::vector<ECAbstractShapeFactory*> filledShapes;
	filledShapes.push_back(new ECFilledRectangleFactory);
	filledShapes.push_back(new ECFilledEllipseFactory);

	factories.push_back(hollowShapes);
	factories.push_back(filledShapes);
	selectedShapeFactory = factories[0][0];
}

ECShapeManager::~ECShapeManager() {
	selectedShapeFactory = NULL;
	for (auto row : factories) {
		for (auto item : row) {
			delete item;
		}
	}
}

ECShape* ECShapeManager::GenerateSelectedShapeType(int xS, int yS, int xE, int yE) {
	return selectedShapeFactory->CreateShape(xS, yS, xE, yE);
}

void ECShapeManager::ChangeSelectedShape(ECAbstractShapeFactory* fact){
	selectedShapeFactory = fact;
}

ECAbstractShapeFactory* ECShapeManager::GetSelectedShape() const {
	return selectedShapeFactory;
}

void ECShapeManager::ToggleShapeType() {
	col++;
	if (col >= factories[0].size()) col = 0;
	ChangeSelectedShape(factories[row][col]);
}
void ECShapeManager::TeggleFilledShape() {
	row++;
	if (row >= factories.size()) row = 0;
	ChangeSelectedShape(factories[row][col]);
}
