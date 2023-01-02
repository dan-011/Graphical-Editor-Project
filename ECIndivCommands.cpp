#include "ECIndivCommands.h"

//************************************************************************************************************
// ECInsertShapeCommand
ECInsertShapeCommand::ECInsertShapeCommand(ECModel& mdl, ECShape* shp) : model(mdl), shape(shp), index(-1) {}
ECInsertShapeCommand::~ECInsertShapeCommand() {
    if (shape != NULL) delete shape;
}

void ECInsertShapeCommand::Execute() {
    if (index < 0) {
        model.AddShape(shape);
        index = model.GetNumShapes() - 1;
    }
    else {
        model.SetShapeAt(index, shape);
    }
    shape->SetColor(ECGV_BLACK);
    shape = NULL;
}

void ECInsertShapeCommand::UnExecute() {
    shape = model.GetShapeAt(index);
    model.SetShapeAt(index, NULL);
}

//************************************************************************************************************
// ECDeleteShapeCommand
ECDeleteShapeCommand::ECDeleteShapeCommand(ECModel& mdl, int shapeIndex) : model(mdl), index(shapeIndex) {
    if (index == 0) indices = model.GetMultiSelectIndices();
    else indices.push_back(index);
    model.BreakMultiSelect();
    for (int i = 0; i < (int)indices.size(); i++) shapes.push_back(NULL);
}

ECDeleteShapeCommand::~ECDeleteShapeCommand() {
    for (auto shape : shapes) {
        if (shape != NULL) delete shape;
    }
}

void ECDeleteShapeCommand::Execute() {
    for (int i = 0; i < (int)indices.size(); i++) {
        shapes.at(i) = model.GetShapeAt(indices.at(i));
        model.SetColorAt(indices.at(i), ECGV_BLACK);
        model.SetShapeAt(indices.at(i), NULL);
    }
}

void ECDeleteShapeCommand::UnExecute() {
    for (int i = 0; i < (int)indices.size(); i++) {
        model.SetShapeAt(indices.at(i), shapes.at(i));
        shapes.at(i) = NULL;
    }
}

//************************************************************************************************************
// ECMoveShapeCommand
ECMoveShapeCommand::ECMoveShapeCommand(ECModel& mdl, int shapeIndex, const EC2DPoint& startPoint, const EC2DPoint& curPos, const EC2DPoint& endPoint) : model(mdl), index(shapeIndex), sP(startPoint), cP(curPos), eP(endPoint) {
    indices.push_back(index);
}
ECMoveShapeCommand::~ECMoveShapeCommand() {}

void ECMoveShapeCommand::Execute() {
    for (int i : indices) {
        ECShape* shape = model.GetShapeAt(i);
        shape->Move(cP, eP, model.GetViewWidth(), model.GetViewHeight());
    }
    cP = eP;
    if (index == 0) {
        indices.clear();
        indices = model.GetMultiSelectIndices();
        index = -1;
    }
}

void ECMoveShapeCommand::UnExecute() {
    model.BreakMultiSelect();
    for (int i : indices) {
        ECShape* shape = model.GetShapeAt(i);
        shape->Move(eP, sP, model.GetViewWidth(), model.GetViewHeight());
        model.SetColorAt(i, ECGV_BLACK);
    }
    cP = sP;
}

//************************************************************************************************************
// ECShiftShapeCommand
ECShiftShapeCommand::ECShiftShapeCommand(ECModel& mdl, int shapeIndex, int shiftX, int shiftY) : model(mdl), index(shapeIndex), _shiftX(shiftX), _shiftY(shiftY) {
    indices.push_back(index);
}
ECShiftShapeCommand::~ECShiftShapeCommand() {}
void ECShiftShapeCommand::Execute() {
    for (int i : indices) {
        model.GetShapeAt(i)->Shift(_shiftX, _shiftY, model.GetViewWidth(), model.GetViewHeight());
    }
    if (index == 0) {
        indices.clear();
        indices = model.GetMultiSelectIndices();
        index = -1;
    }
}
void ECShiftShapeCommand::UnExecute() {
    model.BreakMultiSelect();
    for (int i : indices) {
        model.GetShapeAt(i)->Shift(-1 * _shiftX, -1 * _shiftY, model.GetViewWidth(), model.GetViewHeight());
    }
}

//************************************************************************************************************
// ECGroupShapesCommand
ECGroupShapesCommand::ECGroupShapesCommand(ECModel& mdl): model(mdl), grouping(NULL), posInMdl(-1) {
    indices = model.GetMultiSelectIndices();
}
ECGroupShapesCommand::~ECGroupShapesCommand() {
    if (grouping != NULL) delete grouping;
}
void ECGroupShapesCommand::Execute() {
    if (posInMdl < 0) {
        model.GroupSelectedShapes();
        posInMdl = model.GetNumShapes() - 1;
    }
    else {
        for (int i : indices) {
            grouping->AddChild(model.GetShapeAt(i));
            model.SetShapeAt(i, NULL);
        }
        model.SetShapeAt(posInMdl, grouping);
        grouping = NULL;
    }
    model.ClearSelectedShapes();
}
void ECGroupShapesCommand::UnExecute() {
    grouping = model.GetShapeAt(posInMdl);
    for (int i = 0; i < grouping->GetNumShapes(); i++) {
        model.SetShapeAt(grouping->GetLocationAt(i), grouping->RemoveChild(i));
    }
    grouping->ClearShapes();
    model.SetShapeAt(posInMdl, NULL);
}

//************************************************************************************************************
// ECUnGroupShapesCommand
ECUnGroupShapesCommand::ECUnGroupShapesCommand(ECModel& mdl, int position) : model(mdl), grouping(NULL), posInMdl(position) {}
ECUnGroupShapesCommand::~ECUnGroupShapesCommand() {
    if (grouping != NULL) delete grouping;
}
void ECUnGroupShapesCommand::Execute() {
    grouping = model.GetShapeAt(posInMdl);
    if (grouping->GetNumLocations() > 0) {
        for (int i = 0; i < grouping->GetNumShapes(); i++) {
            model.SetShapeAt(grouping->GetLocationAt(i), grouping->RemoveChild(i));
        }
    }
    else {
        for (int i = 0; i < grouping->GetNumShapes(); i++) {
            model.AddShape(grouping->RemoveChild(i));
            grouping->AddLocation(model.GetNumShapes() - 1);
        }
    }
    grouping->ClearShapes();
    model.SetShapeAt(posInMdl, NULL);
}
void ECUnGroupShapesCommand::UnExecute() {
    for (int i = 0; i < grouping->GetNumLocations(); i++) {
        grouping->AddChild(model.GetShapeAt(grouping->GetLocationAt(i)));
        model.SetShapeAt(grouping->GetLocationAt(i), NULL);
    }
    model.SetShapeAt(posInMdl, grouping);
    grouping = NULL;
}