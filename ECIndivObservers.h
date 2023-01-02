#ifndef __ECINDIVOBSERVERS_H
#define __ECINDIVOBSERVERS_H

#include "ECGraphicViewImp.h"
#include "ECObserver.h"
#include "ECModel.h"

//************************************************************************************************************
// ECModeChangeObserver
class ECModeChangeObserver : public ECObserver {
public:
    ECModeChangeObserver(ECGraphicViewImp& vw, ECModel& mdl);
    virtual ~ECModeChangeObserver();
    virtual void Update() override;

private:
    ECGraphicViewImp& view;
    ECModel& model;
};

//************************************************************************************************************
// ECMouseDownObserver
class ECMouseDownObserver : public ECObserver {
public:
    ECMouseDownObserver(ECGraphicViewImp& vw, ECModel& mdl);
    virtual ~ECMouseDownObserver();
    virtual void Update() override;

private:
    ECGraphicViewImp& view;
    ECModel& model;
};

//************************************************************************************************************
// ECDraggingObserver
class ECDraggingObserver : public ECObserver {
public:
    ECDraggingObserver(ECGraphicViewImp& vw, ECModel& mdl);
    virtual ~ECDraggingObserver();
    virtual void Update() override;

private:
    ECGraphicViewImp& view;
    ECModel& model;
};

//************************************************************************************************************
// ECMouseUpObserver
class ECMouseUpObserver : public ECObserver {
public:
    ECMouseUpObserver(ECGraphicViewImp& vw, ECModel& mdl);
    virtual ~ECMouseUpObserver();
    virtual void Update() override;

private:
    ECGraphicViewImp& view;
    ECModel& model;
};

//************************************************************************************************************
// ECDeleteShapeObserver
class ECDeleteShapeObserver : public ECObserver {
public:
    ECDeleteShapeObserver(ECGraphicViewImp& vw, ECModel& mdl);
    virtual ~ECDeleteShapeObserver();
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    ECModel& model;
};

//************************************************************************************************************
// ECTimerObserver
class ECTimerObserver : public ECObserver {
public:
    ECTimerObserver(ECGraphicViewImp& vw, ECModel& mdl);
    virtual ~ECTimerObserver();
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    ECModel& model;
};

//************************************************************************************************************
// ECUndoObserver
class ECUndoObserver : public ECObserver {
public:
    ECUndoObserver(ECGraphicViewImp& vw, ECModel& mdl);
    virtual ~ECUndoObserver();
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    ECModel& model;
};

//************************************************************************************************************
// ECRedoObserver
class ECRedoObserver : public ECObserver {
public:
    ECRedoObserver(ECGraphicViewImp& vw, ECModel& mdl);
    virtual ~ECRedoObserver();
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    ECModel& model;
};

//************************************************************************************************************
// ECChangeShapeObserver
class ECGKeyObserver : public ECObserver {
public:
    ECGKeyObserver(ECGraphicViewImp& vw, ECModel& mdl);
    virtual ~ECGKeyObserver();
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    ECModel& model;
};

//************************************************************************************************************
// ECFKeyObserver
class ECFKeyObserver : public ECObserver {
public:
    ECFKeyObserver(ECGraphicViewImp& vw, ECModel& mdl);
    virtual ~ECFKeyObserver();
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    ECModel& model;
};

//************************************************************************************************************
// ECUpKeyObserver
class ECUpKeyObserver : public ECObserver {
public:
    ECUpKeyObserver(ECGraphicViewImp& vw, ECModel& mdl);
    virtual ~ECUpKeyObserver();
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    ECModel& model;
};

//************************************************************************************************************
// ECDownKeyObserver
class ECDownKeyObserver : public ECObserver {
public:
    ECDownKeyObserver(ECGraphicViewImp& vw, ECModel& mdl);
    virtual ~ECDownKeyObserver();
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    ECModel& model;
};

//************************************************************************************************************
// ECLeftKeyObserver
class ECLeftKeyObserver : public ECObserver {
public:
    ECLeftKeyObserver(ECGraphicViewImp& vw, ECModel& mdl);
    virtual ~ECLeftKeyObserver();
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    ECModel& model;
};

//************************************************************************************************************
// ECRightKeyObserver
class ECRightKeyObserver : public ECObserver {
public:
    ECRightKeyObserver(ECGraphicViewImp& vw, ECModel& mdl);
    virtual ~ECRightKeyObserver();
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    ECModel& model;
};

//************************************************************************************************************
// ECCtrlKeyDownObserver
class ECCtrlKeyDownObserver : public ECObserver {
public:
    ECCtrlKeyDownObserver(ECGraphicViewImp& vw, ECModel& mdl);
    virtual ~ECCtrlKeyDownObserver();
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    ECModel& model;
};

//************************************************************************************************************
// ECCtrlKeyUpObserver
class ECCtrlKeyUpObserver : public ECObserver {
public:
    ECCtrlKeyUpObserver(ECGraphicViewImp& vw, ECModel& mdl);
    virtual ~ECCtrlKeyUpObserver();
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    ECModel& model;
};
#endif