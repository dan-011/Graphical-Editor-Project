#ifndef __ECSHAPEFILEOBSERVERS_H
#define __ECSHAPEFILEOBSERVERS_H

#include "ECShapeFileSubject.h"

//************************************************************************************************************
// ECRectangleFileObserver
class ECRectangleFileObserver : public ECShapeFileObserver {
public:
	ECRectangleFileObserver(ECShapeFileSubject& subj);
	virtual ~ECRectangleFileObserver();
	void Update() override;
private:
	ECShapeFileSubject& subject;
};

//************************************************************************************************************
// ECEllipseFileObserver
class ECEllipseFileObserver : public ECShapeFileObserver {
public:
	ECEllipseFileObserver(ECShapeFileSubject& subj);
	virtual ~ECEllipseFileObserver();
	void Update() override;
private:
	ECShapeFileSubject& subject;
};

//************************************************************************************************************
// ECFilledRectangleFileObserver
class ECFilledRectangleFileObserver : public ECShapeFileObserver {
public:
	ECFilledRectangleFileObserver(ECShapeFileSubject& subj);
	virtual ~ECFilledRectangleFileObserver();
	void Update() override;
private:
	ECShapeFileSubject& subject;
};

//************************************************************************************************************
// ECFilledEllipseFileObserver
class ECFilledEllipseFileObserver : public ECShapeFileObserver {
public:
	ECFilledEllipseFileObserver(ECShapeFileSubject& subj);
	virtual ~ECFilledEllipseFileObserver();
	void Update() override;
private:
	ECShapeFileSubject& subject;
};

//************************************************************************************************************
// ECCompositeFileObserver
class ECCompositeFileObserver : public ECShapeFileObserver {
public:
	ECCompositeFileObserver(ECShapeFileSubject& subj);
	virtual ~ECCompositeFileObserver();
	void Update() override;
private:
	ECShapeFileSubject& subject;
};
#endif