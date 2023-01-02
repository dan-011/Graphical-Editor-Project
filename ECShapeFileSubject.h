#ifndef __ECSHAPEFILESUBJECT_H
#define __ECSHAPEFILESUBJECT_H

#include <stack>
#include <vector>
#include "ECShapeManager.h"

//************************************************************************************************************
// ECShapeFileObserver
class ECShapeFileObserver {
public:
	virtual ~ECShapeFileObserver() {}
	virtual void Update() = 0;

protected:
	ECShapeManager& GetShapeManager();

private:
	ECShapeManager shapeManager;
};

//************************************************************************************************************
// ECShapeFileSubject
class ECShapeFileSubject {
public:
	ECShapeFileSubject();
	~ECShapeFileSubject();
	void AddObserver(ECShapeFileObserver* observer);
	void Notify();
	void SetShape(ECShape* shape);
	ECShape* GetShape() const;
	ECShape* PopShape();
	std::vector<int> GetLine() const;
	void SetLine(const std::vector<int>& fileLine);
	bool GetShapeIsReady() const;
	void SetShapeIsReady(bool ready);
	void PushCompositeShapeSize(int sz);

private:
	std::stack<int> compositeShapeSize;
	std::stack<ECShape*> shapeStack;
	std::vector<ECShapeFileObserver*> observers;
	bool isReady;
	std::vector<int> line;
};
#endif