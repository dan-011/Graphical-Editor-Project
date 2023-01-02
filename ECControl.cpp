#include "ECControl.h"

//************************************************************************************************************
// ECControl
ECControl::ECControl(ECModel& mdl) : model(mdl), mouseClicked(false), ctrlDown(false) {}
ECControl::~ECControl() {}

void ECControl::ToggleMode() {
	model.BreakMultiSelect();
	if (model.GetTraceShapeVisibility()) {
		model.SetTraceShape(NULL);
		mouseClicked = false;
	}
	ECEditCtrl* editCtrl = dynamic_cast<ECEditCtrl*>(model.GetControl());
	if (editCtrl != NULL) {
		model.ClearSelectedShapes();
		if(mouseClicked || editCtrl->GetSelectedShapeIndex() >= 0) editCtrl->RevertSelectedShape();
	}
	model.ShiftControl();
	model.ReDraw();
}

bool ECControl::Undo() {
	model.ClearSelectedShapes();
	return GetCommandHistory().Undo();
}

bool ECControl::Redo() {
	model.ClearSelectedShapes();
	return GetCommandHistory().Redo();
}

void ECControl::DKey() {}

void ECControl::GKey() {}

void ECControl::FKey() {}

void ECControl::UpKey() {}
void ECControl::DownKey() {}
void ECControl::LeftKey() {}
void ECControl::RightKey() {}
void ECControl::CtrlKeyDown() {
	ctrlDown = true;
}
void ECControl::CtrlKeyUp() {
	ctrlDown = false;
}
bool ECControl::GetCtrlDown() const {
	return ctrlDown;
}

ECModel& ECControl::GetModel() {
	return model;
}

bool ECControl::GetMouseClicked() const {
	return mouseClicked;
}
void ECControl::SetMouseClicked(bool wasClicked) {
	mouseClicked = wasClicked;
}

//************************************************************************************************************
// ECInsertionCtrl
ECInsertionCtrl::ECInsertionCtrl(ECModel& mdl) : ECControl(mdl){
}
ECInsertionCtrl::~ECInsertionCtrl() {
}

void ECInsertionCtrl::MouseDown(int x, int y) {
	ECShapeManager localShapeManager;
	GetModel().SetTraceShape(localShapeManager.GenerateSelectedShapeType(x, y, x, y));
	SetMouseClicked(true);
	GetModel().ReDraw();
}

void ECInsertionCtrl::Dragging(int x, int y) {
	if (!GetMouseClicked()) return;
	EC2DPoint traceStartPoint = GetModel().GetTraceShape()->GetDrawPoints().first;
	GetModel().SetTraceShape(traceStartPoint.GetX(), traceStartPoint.GetY(), x, y);
	GetModel().ReDraw();
}

void ECInsertionCtrl::MouseUp(int x, int y) {
	if(!GetMouseClicked()) return;
	EC2DPoint traceStartPoint = GetModel().GetTraceShape()->GetDrawPoints().first;
	ECShape* shape = shapeManager.GenerateSelectedShapeType(traceStartPoint.GetX(), traceStartPoint.GetY(), x, y);
	shape->SetColor(ECGV_BLACK);
	shape->SetThickness(3);
	ECCommand* insertShapeCommand = new ECInsertShapeCommand(GetModel(), shape);
	GetCommandHistory().ExecuteCmd(insertShapeCommand);
	GetModel().SetTraceShape(NULL);
	SetMouseClicked(false);
	GetModel().ReDraw();
}

void ECInsertionCtrl::GKey() {
	ToggleSelectedShape();
}

void ECInsertionCtrl::ToggleSelectedShape() {
	shapeManager.ToggleShapeType();
}

void ECInsertionCtrl::FKey() {
	shapeManager.TeggleFilledShape();
}

//************************************************************************************************************
// ECEditCtrl
ECEditCtrl::ECEditCtrl(ECModel& mdl) : ECControl(mdl), selectedShapeIndex(-1), startPos(-1, -1), curPos(-1, -1) {}
ECEditCtrl::~ECEditCtrl() {}

void ECEditCtrl::MouseDown(int x, int y) {
	if (selectedShapeIndex > 0 && GetCtrlDown()) GetModel().AddToMultiSelect(selectedShapeIndex);
	SetMouseClicked(true);
	GetModel().ClearSelectedShapes();
	selectedShapeIndex = GetModel().GetShapeIndex(x, y);
	if (GetCtrlDown()) selectedShapeIndex = GetModel().AddToMultiSelect(x, y);
	if (selectedShapeIndex < 0) return;
	GetModel().SetColorAt(selectedShapeIndex, ECGV_BLUE);
	startBoundingPoints = GetModel().GetShapeAt(selectedShapeIndex)->GetDrawPoints();
	startPos = EC2DPoint(x, y);
	curPos = startPos;
	GetModel().ReDraw();
}

void ECEditCtrl::Dragging(int x, int y) {
	if (!GetMouseClicked()) return;
	if (selectedShapeIndex < 0) return;
	ECShape* shape = GetModel().GetShapeAt(selectedShapeIndex);
	EC2DPoint endPos(x, y);
	shape->Move(curPos, endPos, GetModel().GetViewWidth(), GetModel().GetViewHeight());
	curPos = endPos;
	GetModel().ReDraw();
}

void ECEditCtrl::MouseUp(int x, int y) {
	SetMouseClicked(false);
	if (selectedShapeIndex < 0) return;
	if (startPos.GetX() - x == 0 && startPos.GetY() - y == 0) {
		if (!GetCtrlDown()) GetModel().BreakMultiSelect();
		selectedShapeIndex = GetModel().GetShapeIndex(x, y);
		GetModel().SetColorAt(selectedShapeIndex, ECGV_BLUE);
		return;
	}
	EC2DPoint endPos(x, y);
	ECCommand* moveShapeCommand = new ECMoveShapeCommand(GetModel(), selectedShapeIndex, startPos, endPos, endPos);
	GetCommandHistory().ExecuteCmd(moveShapeCommand);
	startPos = EC2DPoint(-1, -1);
	GetModel().ReDraw();
}

void ECEditCtrl::DKey() {
	if (selectedShapeIndex < 0) return;
	int index = selectedShapeIndex;
	if(GetMouseClicked()) RevertSelectedShape();
	ECCommand* deleteShapeCommand = new ECDeleteShapeCommand(GetModel(), index);
	GetCommandHistory().ExecuteCmd(deleteShapeCommand);
	selectedShapeIndex = -1;
	GetModel().ReDraw();
}

void ECEditCtrl::GKey() {
	if (selectedShapeIndex < 0) return;
	ECShape* multiselect = GetModel().GetShapeAt(0);
	if (selectedShapeIndex == 0 && multiselect->GetNumShapes() == 1 && multiselect->GetShapeAt(0)->GetNumShapes() > 1) {
		selectedShapeIndex = GetModel().GetIndexInMultiSelect(0);
		GetModel().BreakMultiSelect();
	}
	if (selectedShapeIndex != 0 && GetModel().GetShapeAt(selectedShapeIndex)->GetNumShapes() > 1) {
		ECUnGroupShapesCommand* unGroupShapesCommand = new ECUnGroupShapesCommand(GetModel(), selectedShapeIndex);
		GetCommandHistory().ExecuteCmd(unGroupShapesCommand);

	}
	if (selectedShapeIndex == 0) {
		ECGroupShapesCommand* groupShapesCommand = new ECGroupShapesCommand(GetModel());
		GetCommandHistory().ExecuteCmd(groupShapesCommand);
	}
	GetModel().ClearSelectedShapes();
	selectedShapeIndex = -1;
	GetModel().ReDraw();
}

void ECEditCtrl::UpKey() {
	if (GetSelectedShapeIndex() < 0) return;
	ECShiftShapeCommand* cmd = new ECShiftShapeCommand(GetModel(), GetSelectedShapeIndex(), 0, -10);
	GetCommandHistory().ExecuteCmd(cmd);
	GetModel().ReDraw();
}
void ECEditCtrl::DownKey() {
	if (GetSelectedShapeIndex() < 0) return;
	ECShiftShapeCommand* cmd = new ECShiftShapeCommand(GetModel(), GetSelectedShapeIndex(), 0, 10);
	GetCommandHistory().ExecuteCmd(cmd);
	GetModel().ReDraw();
}
void ECEditCtrl::LeftKey() {
	if (GetSelectedShapeIndex() < 0) return;
	ECShiftShapeCommand* cmd = new ECShiftShapeCommand(GetModel(), GetSelectedShapeIndex(), -10, 0);
	GetCommandHistory().ExecuteCmd(cmd);
	GetModel().ReDraw();
}
void ECEditCtrl::RightKey() {
	if (GetSelectedShapeIndex() < 0) return;
	ECShiftShapeCommand* cmd = new ECShiftShapeCommand(GetModel(), GetSelectedShapeIndex(), 10, 0);
	GetCommandHistory().ExecuteCmd(cmd);
	GetModel().ReDraw();
}

void ECEditCtrl::RevertSelectedShape() {
	if (selectedShapeIndex < 0) return;
	if (GetMouseClicked()) {
		GetModel().SetShapeAt(selectedShapeIndex, startBoundingPoints.first.GetX(), startBoundingPoints.first.GetY(), startBoundingPoints.second.GetX(), startBoundingPoints.second.GetY());
		SetMouseClicked(false);
	}
	selectedShapeIndex = -1;
}

int ECEditCtrl::GetSelectedShapeIndex() const {
	return selectedShapeIndex;
}
void ECEditCtrl::SetSelectedShapeIndex(int index) {
	selectedShapeIndex = index;
}

