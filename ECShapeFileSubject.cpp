#include "ECShapeFileSubject.h"

//************************************************************************************************************
// ECShapeFileObserver
ECShapeManager& ECShapeFileObserver::GetShapeManager() {
	return shapeManager;
}

//************************************************************************************************************
// ECShapeFileSubject
ECShapeFileSubject::ECShapeFileSubject(): isReady(true) {}
ECShapeFileSubject::~ECShapeFileSubject() {
	for (auto observer : observers) {
		if (observer != NULL) delete observer;
	}
}
void ECShapeFileSubject::AddObserver(ECShapeFileObserver* observer) {
	observers.push_back(observer);
}
void ECShapeFileSubject::Notify() {
	for (auto observer : observers) {
		observer->Update();
	}
}
void ECShapeFileSubject::SetShape(ECShape* shape) {
	if (!isReady) {
		shapeStack.top()->AddChild(shape);
	}
	else {
		shapeStack.push(shape);
	}
}
ECShape* ECShapeFileSubject::PopShape() {
	if (isReady) {
		ECShape* ret = shapeStack.top();
		shapeStack.pop();
		return ret;
	}
	else {
		return NULL;
	}
}
ECShape* ECShapeFileSubject::GetShape() const {
	return shapeStack.top();
}
std::vector<int> ECShapeFileSubject::GetLine() const {
	return line;
}
void ECShapeFileSubject::SetLine(const std::vector<int>& fileLine) {
	line = fileLine;
	Notify();
	if (!isReady) {
		compositeShapeSize.top()--;
	}
	while (compositeShapeSize.size() > 0 && compositeShapeSize.top() == 0) {
		compositeShapeSize.pop();
		if (shapeStack.size() > 1) {
			ECShape* shape = shapeStack.top();
			shapeStack.pop();
			compositeShapeSize.top()--;
			shapeStack.top()->AddChild(shape);
		}
	}
	SetShapeIsReady(compositeShapeSize.size() == 0);
}
bool ECShapeFileSubject::GetShapeIsReady() const {
	return isReady;
}
void ECShapeFileSubject::SetShapeIsReady(bool ready) {
	isReady = ready;
}
void ECShapeFileSubject::PushCompositeShapeSize(int sz) {
	compositeShapeSize.push(sz);
}