#ifndef __ECINDIVCOMMANDS_H
#define __ECINDIVCOMMANDS_H

#include "ECModel.h"

//************************************************************************************************************
// ECInsertShapeCommand
class ECInsertShapeCommand : public ECCommand {
public:
    ECInsertShapeCommand(ECModel& mdl, ECShape* shp);
    virtual ~ECInsertShapeCommand();
    virtual void Execute() override;
    virtual void UnExecute() override;

private:
    ECModel& model;
    ECShape* shape;
    int index;
};

//************************************************************************************************************
// ECDeleteShapeCommand
class ECDeleteShapeCommand : public ECCommand {
public:
    ECDeleteShapeCommand(ECModel& mdl, int shapeIndex);
    virtual ~ECDeleteShapeCommand();
    virtual void Execute() override;
    virtual void UnExecute() override;

private:
    ECModel& model;
    int index;
    std::vector<int> indices;
    std::vector<ECShape*> shapes;
};

class ECMoveShapeCommand : public ECCommand {
public:
    ECMoveShapeCommand(ECModel& mdl, int shapeIndex, const EC2DPoint& startPoint, const EC2DPoint& curPos, const EC2DPoint& endPoint);
    virtual ~ECMoveShapeCommand();
    virtual void Execute() override;
    virtual void UnExecute() override;

private:
    ECModel& model;
    int index;
    EC2DPoint sP;
    EC2DPoint cP;
    EC2DPoint eP;
    std::vector<int> indices;
};

//************************************************************************************************************
// ECShiftShapeCommand
class ECShiftShapeCommand : public ECCommand{
public:
    ECShiftShapeCommand(ECModel& mdl, int shapeIndex, int shiftX, int shiftY);
    virtual ~ECShiftShapeCommand();
    virtual void Execute() override;
    virtual void UnExecute() override;

private:
    ECModel& model;
    int index;
    int _shiftX;
    int _shiftY;
    std::vector<int> indices;
};

//************************************************************************************************************
// ECGroupShapesCommand
class ECGroupShapesCommand : public ECCommand {
public:
    ECGroupShapesCommand(ECModel& mdl);
    virtual ~ECGroupShapesCommand();
    virtual void Execute() override;
    virtual void UnExecute() override;

private:
    ECModel& model;
    ECShape* grouping;
    int posInMdl;
    std::vector<int> indices;
};

//************************************************************************************************************
// ECUnGroupShapesCommand
class ECUnGroupShapesCommand : public ECCommand {
public:
    ECUnGroupShapesCommand(ECModel& mdl, int position);
    virtual ~ECUnGroupShapesCommand();
    virtual void Execute() override;
    virtual void UnExecute() override;

private:
    ECModel& model;
    ECShape* grouping;
    int posInMdl;
};
#endif