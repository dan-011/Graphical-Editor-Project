#ifndef __ECFILEHANDLER_H
#define __ECFILEHANDLER_H

#include <fstream>
#include <string>
#include "ECModel.h"
#include "ECShapeFileSubject.h"
#include "ECShapeFileObservers.h"
#include <vector>

//************************************************************************************************************
// ECFileHandler
class ECFileHandler {
public:
	ECFileHandler(ECModel& mdl, const char* fName);
	~ECFileHandler();
	void ImportShapeFile();
	void ExportShapeFile();

private:
	void StringBreak(const std::string inStr, std::vector<int>& values);
	ECModel& model;
	const char* filename;
	ECShapeFileSubject subj;
};

#endif