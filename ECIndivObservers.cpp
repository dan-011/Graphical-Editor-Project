#include "ECIndivObservers.h"

//************************************************************************************************************
// ECModeChangeObserver
ECModeChangeObserver::ECModeChangeObserver(ECGraphicViewImp& vw, ECModel& mdl) : view(vw), model(mdl) {
    view.Attach(this);
}
ECModeChangeObserver::~ECModeChangeObserver() {}
void ECModeChangeObserver::Update() {
	ECGVEventType event = view.GetCurrEvent();
	if (event == ECGV_EV_KEY_DOWN_SPACE) {
		model.GetControl()->ToggleMode();
	}
}

//************************************************************************************************************
// ECMouseDownObserver
ECMouseDownObserver::ECMouseDownObserver(ECGraphicViewImp& vw, ECModel& mdl) : view(vw), model(mdl) {
    view.Attach(this);
}
ECMouseDownObserver::~ECMouseDownObserver() {}
void ECMouseDownObserver::Update() {
    ECGVEventType event = view.GetCurrEvent();
    if (event == ECGV_EV_MOUSE_BUTTON_DOWN) {
        int x;
        int y;
        view.GetCursorPosition(x, y);
        model.GetControl()->MouseDown(x, y);
    }
}

//************************************************************************************************************
// ECDraggingObserver
ECDraggingObserver::ECDraggingObserver(ECGraphicViewImp& vw, ECModel& mdl) : view(vw), model(mdl) {
    view.Attach(this);
}
ECDraggingObserver::~ECDraggingObserver() {}
void ECDraggingObserver::Update() {
    ECGVEventType event = view.GetCurrEvent();
    if (event == ECGV_EV_MOUSE_MOVING) {
        int x;
        int y;
        view.GetCursorPosition(x, y);
        model.GetControl()->Dragging(x, y);
    }
}

//************************************************************************************************************
// ECMouseUpObserver
ECMouseUpObserver::ECMouseUpObserver(ECGraphicViewImp& vw, ECModel& mdl) : view(vw), model(mdl) {
    view.Attach(this);
}
ECMouseUpObserver::~ECMouseUpObserver() {}
void ECMouseUpObserver::Update() {
    ECGVEventType event = view.GetCurrEvent();
    if (event == ECGV_EV_MOUSE_BUTTON_UP) {
        int x;
        int y;
        view.GetCursorPosition(x, y);
        model.GetControl()->MouseUp(x, y);
    }
}

//************************************************************************************************************
// ECDeleteShapeObserver
ECDeleteShapeObserver::ECDeleteShapeObserver(ECGraphicViewImp& vw, ECModel& mdl) : view(vw), model(mdl) {
    view.Attach(this);
}
ECDeleteShapeObserver::~ECDeleteShapeObserver() {}
void ECDeleteShapeObserver::Update() {
    ECGVEventType event = view.GetCurrEvent();
    if (event == ECGV_EV_KEY_DOWN_D) {
        model.GetControl()->DKey();
    }
}

//************************************************************************************************************
// ECTimerObserver
ECTimerObserver::ECTimerObserver(ECGraphicViewImp& vw, ECModel& mdl) : view(vw), model(mdl) {
    view.Attach(this);
}
ECTimerObserver::~ECTimerObserver() {}
void ECTimerObserver::Update() {
    ECGVEventType event = view.GetCurrEvent();
    if (event == ECGV_EV_TIMER) {
        model.ReDraw();
    }
}

//************************************************************************************************************
// ECUndoObserver
ECUndoObserver::ECUndoObserver(ECGraphicViewImp& vw, ECModel& mdl) : view(vw), model(mdl) {
    view.Attach(this);
}
ECUndoObserver::~ECUndoObserver() {}
void ECUndoObserver::Update() {
    ECGVEventType event = view.GetCurrEvent();
    if (event == ECGV_EV_KEY_DOWN_Z) {
        model.GetControl()->Undo();
    }
}

//************************************************************************************************************
// ECRedoObserver
ECRedoObserver::ECRedoObserver(ECGraphicViewImp& vw, ECModel& mdl) : view(vw), model(mdl) {
    view.Attach(this);
}
ECRedoObserver::~ECRedoObserver() {}
void ECRedoObserver::Update() {
    ECGVEventType event = view.GetCurrEvent();
    if (event == ECGV_EV_KEY_DOWN_Y) {
        model.GetControl()->Redo();
    }
}

//************************************************************************************************************
// ECGKeyObserver
ECGKeyObserver::ECGKeyObserver(ECGraphicViewImp& vw, ECModel& mdl) : view(vw), model(mdl) {
    view.Attach(this);
}
ECGKeyObserver::~ECGKeyObserver() {}
void ECGKeyObserver::Update() {
    ECGVEventType event = view.GetCurrEvent();
    if (event == ECGV_EV_KEY_UP_G) {
        model.GetControl()->GKey();
    }
}

//************************************************************************************************************
// ECFKeyObserver
ECFKeyObserver::ECFKeyObserver(ECGraphicViewImp& vw, ECModel& mdl) : view(vw), model(mdl) {
    view.Attach(this);
}
ECFKeyObserver::~ECFKeyObserver() {}
void ECFKeyObserver::Update() {
    ECGVEventType event = view.GetCurrEvent();
    if (event == ECGV_EV_KEY_UP_F) {
        model.GetControl()->FKey();
    }
}

//************************************************************************************************************
// ECUpKeyObserver
ECUpKeyObserver::ECUpKeyObserver(ECGraphicViewImp& vw, ECModel& mdl) : view(vw), model(mdl) {
    view.Attach(this);
}
ECUpKeyObserver::~ECUpKeyObserver() {}
void ECUpKeyObserver::Update() {
    ECGVEventType event = view.GetCurrEvent();
    if (event == ECGV_EV_KEY_UP_UP) {
        model.GetControl()->UpKey();
    }
}

//************************************************************************************************************
// ECDownKeyObserver
ECDownKeyObserver::ECDownKeyObserver(ECGraphicViewImp& vw, ECModel& mdl) : view(vw), model(mdl) {
    view.Attach(this);
}
ECDownKeyObserver::~ECDownKeyObserver() {}
void ECDownKeyObserver::Update() {
    ECGVEventType event = view.GetCurrEvent();
    if (event == ECGV_EV_KEY_UP_DOWN) {
        model.GetControl()->DownKey();
    }
}

//************************************************************************************************************
// ECLeftKeyObserver
ECLeftKeyObserver::ECLeftKeyObserver(ECGraphicViewImp& vw, ECModel& mdl) : view(vw), model(mdl) {
    view.Attach(this);
}
ECLeftKeyObserver::~ECLeftKeyObserver() {}
void ECLeftKeyObserver::Update() {
    ECGVEventType event = view.GetCurrEvent();
    if (event == ECGV_EV_KEY_UP_LEFT) {
        model.GetControl()->LeftKey();
    }
}

//************************************************************************************************************
// ECRightKeyObserver
ECRightKeyObserver::ECRightKeyObserver(ECGraphicViewImp& vw, ECModel& mdl) : view(vw), model(mdl) {
    view.Attach(this);
}
ECRightKeyObserver::~ECRightKeyObserver() {}
void ECRightKeyObserver::Update() {
    ECGVEventType event = view.GetCurrEvent();
    if (event == ECGV_EV_KEY_UP_RIGHT) {
        model.GetControl()->RightKey();
    }
}

//************************************************************************************************************
// ECCtrlKeyDownObserver
ECCtrlKeyDownObserver::ECCtrlKeyDownObserver(ECGraphicViewImp& vw, ECModel& mdl) : view(vw), model(mdl) {
    view.Attach(this);
}
ECCtrlKeyDownObserver::~ECCtrlKeyDownObserver() {}
void ECCtrlKeyDownObserver::Update() {
    ECGVEventType event = view.GetCurrEvent();
    if (event == ECGV_EV_KEY_DOWN_CTRL) {
        model.GetControl()->CtrlKeyDown();
    }
}

//************************************************************************************************************
// ECCtrlKeyUpObserver
ECCtrlKeyUpObserver::ECCtrlKeyUpObserver(ECGraphicViewImp& vw, ECModel& mdl) : view(vw), model(mdl) {
    view.Attach(this);
}
ECCtrlKeyUpObserver::~ECCtrlKeyUpObserver() {}
void ECCtrlKeyUpObserver::Update() {
    ECGVEventType event = view.GetCurrEvent();
    if (event == ECGV_EV_KEY_UP_CTRL) {
        model.GetControl()->CtrlKeyUp();
    }
}
