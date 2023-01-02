#ifndef __ECMODEL_H
#define __ECMODEL_H

#include <vector>
#include "ECShape.h"
#include "ECCommand.h"
#include "ECGraphicViewImp.h"

class ECAbstractControl {
public:
	virtual ~ECAbstractControl() {}
	virtual void ToggleMode() = 0;
	virtual bool Undo() = 0;
	virtual bool Redo() = 0;

	virtual void MouseDown(int x, int y) = 0;
	virtual void Dragging(int x, int y) = 0;

	virtual void MouseUp(int x, int y) = 0;
	virtual void DKey() = 0;
	virtual void GKey() = 0;
	virtual void FKey() = 0;
	virtual void UpKey() = 0;
	virtual void DownKey() = 0;
	virtual void LeftKey() = 0;
	virtual void RightKey() = 0;
	virtual void CtrlKeyDown() = 0;
	virtual void CtrlKeyUp() = 0;
	void TransferHistory(ECAbstractControl* ctrl);

protected:
	ECCommandHistory& GetCommandHistory();

private:
	ECCommandHistory commandHistory;
};

class ECModel {
public:
	ECModel(ECGraphicViewImp& vw);
	~ECModel();
	void ReDraw() const;
	int GetViewWidth() const;
	int GetViewHeight() const;
	ECAbstractControl* GetControl() const;
	void ShiftControl();
	int GetNumShapes() const;
	void AddShape(ECShape* shape);
	void RemoveShape(int shapeIndex);
	ECShape* GetShapeAt(int shapeIndex) const;
	void SetShapeAt(int shapeIndex, ECShape* shape);
	void SetShapeAt(int shapeIndex, int xS, int yS, int xE, int yE);
	int GetShapeIndex(int x, int y) const;
	void SetColorAt(int shapeIndex, ECGVColor color);
	ECGVColor GetColorAt(int shapeIndex) const;
	void ClearSelectedShapes();
	void ClearNotSelectedShapes(int index);
	void SetThickNessAt(int shapeIndex, int t);
	int GetThicknessAt(int shapeIndex) const;
	void SetTraceShape(ECShape* shape);
	void SetTraceShape(int xS, int yS, int xE, int yE);
	ECShape* GetTraceShape() const;
	void SetTraceShapeVisibility(bool isVisible);
	bool GetTraceShapeVisibility() const;
	void AddToMultiSelect(int &index);
	int AddToMultiSelect(int x, int y);
	void BreakMultiSelect();
	void GroupSelectedShapes();
	ECShape* GetMultiSelect() const;
	int GetIndexInMultiSelect(int index) const;
	std::vector<int> GetMultiSelectIndices() const;

private:
	ECGraphicViewImp& view;
	std::vector<ECShape*> listShapes;
	ECShape* traceShape;
	std::vector<ECAbstractControl*> controls;
	int currentControlIndex;
	bool isTraceShapeVisible;
	ECShape* multiSelect;
	std::vector<int> multiSelectIndices;
};

#endif