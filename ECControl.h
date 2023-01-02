#ifndef __ECCONTROL_H
#define __ECCONTROL_H

#include "ECShapeManager.h"
#include "ECIndivCommands.h"
#include "ECModel.h"

//************************************************************************************************************
// ECControl
class ECControl : public ECAbstractControl {
public:
	ECControl(ECModel& mdl);
	virtual ~ECControl();
	void ToggleMode();
	bool Undo();
	bool Redo();
	virtual void MouseUp(int x, int y) = 0;
	virtual void DKey();
	virtual void GKey();
	virtual void FKey();
	virtual void UpKey();
	virtual void DownKey();
	virtual void LeftKey();
	virtual void RightKey();
	virtual void CtrlKeyDown();
	virtual void CtrlKeyUp();

protected:
	ECModel& GetModel();
	bool GetMouseClicked() const;
	void SetMouseClicked(bool wasClicked);
	bool GetCtrlDown() const;

private:
	ECModel& model;
	bool mouseClicked;
	bool ctrlDown;
};

//************************************************************************************************************
// ECInsertionCtrl
class ECInsertionCtrl : public ECControl {
public:
	ECInsertionCtrl(ECModel& model);
	virtual ~ECInsertionCtrl();
	virtual void MouseDown(int x, int y) override;
	virtual void Dragging(int x, int y) override;
	virtual void MouseUp(int x, int y) override;
	virtual void GKey() override;
	virtual void FKey() override;
	//virtual void CtrlKey() override;

private:
	void ToggleSelectedShape();
	ECShapeManager shapeManager;
};

//************************************************************************************************************
// ECEditCtrl
class ECEditCtrl : public ECControl {
public:
	ECEditCtrl(ECModel& model);
	virtual ~ECEditCtrl();
	virtual void MouseDown(int x, int y) override;
	virtual void Dragging(int x, int y) override;
	virtual void MouseUp(int x, int y) override;
	virtual void DKey() override;
	virtual void GKey() override;
	virtual void UpKey() override;
	virtual void DownKey() override;
	virtual void LeftKey() override;
	virtual void RightKey() override;
	virtual void RevertSelectedShape();
	virtual int GetSelectedShapeIndex() const;
	virtual void SetSelectedShapeIndex(int index);
	void ClearMultiSelect();

private:
	int selectedShapeIndex;
	EC2DPoint startPos;
	EC2DPoint curPos;
	std::pair<EC2DPoint, EC2DPoint> startBoundingPoints;
};

#endif