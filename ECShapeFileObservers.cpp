#include "ECShapeFileObservers.h"

//************************************************************************************************************
// ECRectangleFileObserver
ECRectangleFileObserver::ECRectangleFileObserver(ECShapeFileSubject& subj) : subject(subj) {
	subject.AddObserver(this);
}
ECRectangleFileObserver::~ECRectangleFileObserver() {}
void ECRectangleFileObserver::Update() {
	const std::vector<int>& line = subject.GetLine();
	if (line.size() > 0 && line.at(0) == 0) {
		GetShapeManager().ChangeSelectedShape(new ECRectangleFactory);
		int xS = line.at(2);
		int yS = line.at(3);
		int xE = line.at(6);
		int yE = line.at(7);
		ECGVColor color = (ECGVColor)line.back();
		ECShape* shape = GetShapeManager().GenerateSelectedShapeType(xS, yS, xE, yE);
		shape->SetColor(color);
		subject.SetShape(shape);
	}
}

//************************************************************************************************************
// ECEllipseFileObserver
ECEllipseFileObserver::ECEllipseFileObserver(ECShapeFileSubject& subj) : subject(subj) {
	subject.AddObserver(this);
}
ECEllipseFileObserver::~ECEllipseFileObserver() {}
void ECEllipseFileObserver::Update() {
	const std::vector<int>& line = subject.GetLine();
	if (line.size() > 0 && line.at(0) == 1) {
		GetShapeManager().ChangeSelectedShape(new ECEllipseFactory);
		int cx = line.at(1);
		int cy = line.at(2);
		int radX = line.at(3);
		int radY = line.at(4);
		int xS = cx - radX;
		int yS = cy - radY;
		int xE = cx + radX;
		int yE = cy + radY;
		ECGVColor color = (ECGVColor)line.back();
		ECShape* shape = GetShapeManager().GenerateSelectedShapeType(xS, yS, xE, yE);
		shape->SetColor(color);
		subject.SetShape(shape);
	}
}

//************************************************************************************************************
// ECFilledRectangleFileObserver
ECFilledRectangleFileObserver::ECFilledRectangleFileObserver(ECShapeFileSubject& subj) : subject(subj) {
	subject.AddObserver(this);
}
ECFilledRectangleFileObserver::~ECFilledRectangleFileObserver() {}
void ECFilledRectangleFileObserver::Update() {
	const std::vector<int>& line = subject.GetLine();
	if (line.size() > 0 && line.at(0) == 2) {
		GetShapeManager().ChangeSelectedShape(new ECFilledRectangleFactory);
		int xS = line.at(2);
		int yS = line.at(3);
		int xE = line.at(6);
		int yE = line.at(7);
		ECGVColor color = (ECGVColor)line.back();
		ECShape* shape = GetShapeManager().GenerateSelectedShapeType(xS, yS, xE, yE);
		shape->SetColor(color);
		subject.SetShape(shape);
	}
}

//************************************************************************************************************
// ECFilledEllipseFileObserver
ECFilledEllipseFileObserver::ECFilledEllipseFileObserver(ECShapeFileSubject& subj) : subject(subj) {
	subject.AddObserver(this);
}
ECFilledEllipseFileObserver::~ECFilledEllipseFileObserver() {}
void ECFilledEllipseFileObserver::Update() {
	const std::vector<int>& line = subject.GetLine();
	if (line.size() > 0 && line.at(0) == 3) {
		GetShapeManager().ChangeSelectedShape(new ECFilledEllipseFactory);
		int cx = line.at(1);
		int cy = line.at(2);
		int radX = line.at(3);
		int radY = line.at(4);
		int xS = cx - radX;
		int yS = cy - radY;
		int xE = cx + radX;
		int yE = cy + radY;
		ECGVColor color = (ECGVColor)line.back();
		ECShape* shape = GetShapeManager().GenerateSelectedShapeType(xS, yS, xE, yE);
		shape->SetColor(color);
		subject.SetShape(shape);
	}
}

//************************************************************************************************************
// ECCompositeFileObserver
ECCompositeFileObserver::ECCompositeFileObserver(ECShapeFileSubject& subj) : subject(subj) {
	subject.AddObserver(this);
}
ECCompositeFileObserver::~ECCompositeFileObserver() {}
void ECCompositeFileObserver::Update() {
	const std::vector<int>& line = subject.GetLine();
	if (line.size() > 0 && line.at(0) == 4) {
		subject.PushCompositeShapeSize(line.at(1) + 1);
		subject.SetShapeIsReady(true);
		subject.SetShape(new ECCompositeShape);
		subject.SetShapeIsReady(false);
	}
}