#include "ECModel.h"
#include "ECControl.h"

//************************************************************************************************************
// ECAbstractControl
void ECAbstractControl::TransferHistory(ECAbstractControl* ctrl) {
	commandHistory = std::move(ctrl->commandHistory);
}
ECCommandHistory& ECAbstractControl::GetCommandHistory() {
	return commandHistory;
}

//************************************************************************************************************
// ECModel
ECModel::ECModel(ECGraphicViewImp& vw) : view(vw), currentControlIndex(0), traceShape(NULL), isTraceShapeVisible(false), multiSelect(new ECCompositeShape) {
	listShapes.push_back(multiSelect);
	controls.push_back(new ECEditCtrl(*this));
	controls.push_back(new ECInsertionCtrl(*this));
}

ECModel::~ECModel() {
	BreakMultiSelect();
	for (auto control : controls) {
		if (control != NULL) delete control;
	}
	for (auto shape : listShapes) {
		if (shape != NULL) delete shape;
	}
	if (traceShape != NULL) delete traceShape;
}

void ECModel::ReDraw() const {
	view.SetRedraw(true);
	for (auto shape : listShapes) {
		if (shape != NULL) {
			shape->Draw(view);
		}
	}
	if (GetTraceShapeVisibility()) {
		traceShape->Draw(view);
	}
}

int ECModel::GetViewWidth() const {
	return view.GetWith();
}

int ECModel::GetViewHeight() const {
	return view.GetHeight();
}

ECAbstractControl* ECModel::GetControl() const {
	return controls[currentControlIndex];
}

void ECModel::ShiftControl() {
	int prevIndex = currentControlIndex;
	currentControlIndex++;
	if (currentControlIndex >= controls.size()) currentControlIndex = 0;
	controls[currentControlIndex]->TransferHistory(controls[prevIndex]);
}

int ECModel::GetNumShapes() const {
	return (int)listShapes.size();
}

void ECModel::AddShape(ECShape* shape) {
	listShapes.push_back(shape);
}

void ECModel::RemoveShape(int shapeIndex) {
	if (shapeIndex >= listShapes.size()) {
		throw "Cannot remove shape outside of bounds";
	}
	ECShape* ptr = GetShapeAt(shapeIndex);
	listShapes.erase(listShapes.begin() + shapeIndex);
	if (ptr != NULL) delete ptr;
}

ECShape* ECModel::GetShapeAt(int shapeIndex) const {
	if (shapeIndex >= (int)listShapes.size()) throw "Cannot get shape beyond bounds";
	return listShapes.at(shapeIndex);
}

void ECModel::SetShapeAt(int shapeIndex, ECShape* shape) {
	if (shapeIndex >= (int)listShapes.size()) throw "Cannot set shape beyond bounds";
	listShapes[shapeIndex] = shape;
}

void ECModel::SetShapeAt(int shapeIndex, int xS, int yS, int xE, int yE) {
	if (shapeIndex >= (int)listShapes.size()) throw "Cannot set shape beyond bounds";
	ECShape* shape = GetShapeAt(shapeIndex);
	if (shape != NULL) shape->Resize(xS, yS, xE, yE);
}

int ECModel::GetShapeIndex(int x, int y) const {
	EC2DPoint cursorPoint(x, y);
	for (int i = ((int)listShapes.size()) - 1; i >= 0; i--) {
		ECShape* shape = listShapes[i];
		if (shape != NULL && shape->IsPointInside(cursorPoint)) {
			return i;
		}
	}
	return -1;
}

void ECModel::SetColorAt(int shapeIndex, ECGVColor color) {
	ECShape* shp = GetShapeAt(shapeIndex);
	if (shp != NULL) shp->SetColor(color);
}

ECGVColor ECModel::GetColorAt(int shapeIndex) const {
	ECShape* shp = GetShapeAt(shapeIndex);
	if (shp == NULL) return ECGV_NONE;
	else return shp->GetColor();
}

void ECModel::ClearSelectedShapes() {
	for (auto shape : listShapes) {
		if (shape != NULL) {
			shape->SetColor(ECGV_BLACK);
		}
	}
}

void ECModel::ClearNotSelectedShapes(int index) {
	for (int i = 0; i < (int)listShapes.size(); i++) {
		if (i != index)
			SetColorAt(index, ECGV_BLACK);
	}
}

void ECModel::SetThickNessAt(int shapeIndex, int t) {
	ECShape* shp = GetShapeAt(shapeIndex);
	if (shp != NULL) shp->SetThickness(t);
}

int ECModel::GetThicknessAt(int shapeIndex) const {
	ECShape* shp = GetShapeAt(shapeIndex);
	if (shp == NULL) return -1;
	else return shp->GetThickness();
}

void ECModel::SetTraceShape(ECShape* shape) {
	ECShape* ptr = traceShape;
	traceShape = shape;
	if (traceShape != NULL) {
		traceShape->SetColor(ECGV_PURPLE);
		traceShape->SetThickness(1);
		SetTraceShapeVisibility(true);
	}
	else {
		SetTraceShapeVisibility(false);
	}
	if(ptr != NULL) delete ptr;
}

void ECModel::SetTraceShape(int xS, int yS, int xE, int yE) {
	if (traceShape != NULL) {
		traceShape->Resize(xS, yS, xE, yE);
		traceShape->SetColor(ECGV_PURPLE);
		traceShape->SetThickness(1);
		SetTraceShapeVisibility(true);
	}
}

ECShape* ECModel::GetTraceShape() const {
	if (!GetTraceShapeVisibility()) throw "Trace shape is not visible";
	return traceShape;
}

void ECModel::SetTraceShapeVisibility(bool isVisible) {
	isTraceShapeVisible = isVisible;
}

bool ECModel::GetTraceShapeVisibility() const {
	return isTraceShapeVisible;
}

void ECModel::AddToMultiSelect(int &index) {
	if (index != 0) {
		multiSelect->AddChild(GetShapeAt(index), index);
		multiSelectIndices.push_back(index);
		SetShapeAt(index, NULL);
		index = 0;
	}
	else {
		BreakMultiSelect();
	}
}

int ECModel::AddToMultiSelect(int x, int y) {
	int index = GetShapeIndex(x, y);
	if (index > 0) {
		multiSelect->AddChild(GetShapeAt(index), index);
		multiSelectIndices.push_back(index);
		SetShapeAt(index, NULL);
		index = 0;
	}
	else if(index < 0) {
		BreakMultiSelect();
	}
	return index;
}

void ECModel::BreakMultiSelect() {
	ClearSelectedShapes();
	for (int i = 0; i < multiSelect->GetNumShapes(); i++) {
		SetShapeAt(multiSelectIndices[i], multiSelect->GetShapeAt(i));
	}
	multiSelect->ClearShapes();
	multiSelectIndices.clear();
}

void ECModel::GroupSelectedShapes() {
	AddShape(multiSelect);
	multiSelectIndices.clear();
	SetShapeAt(0, new ECCompositeShape);
	multiSelect = GetShapeAt(0);
}

int ECModel::GetIndexInMultiSelect(int index) const {
	return multiSelectIndices.at(index);
}

ECShape* ECModel::GetMultiSelect() const {
	return multiSelect;
}

std::vector<int> ECModel::GetMultiSelectIndices() const {
	return multiSelectIndices;
}