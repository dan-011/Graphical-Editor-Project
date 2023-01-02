#include "ECFileHandler.h"

//************************************************************************************************************
// ECFileHandler
ECFileHandler::ECFileHandler(ECModel& mdl, const char* fName) : model(mdl), filename(fName) {
	ECRectangleFileObserver* rectangleObserver = new ECRectangleFileObserver(subj);
	ECEllipseFileObserver* ellipseObserver = new ECEllipseFileObserver(subj);
	ECFilledRectangleFileObserver* filledRectangleObserver = new ECFilledRectangleFileObserver(subj);
	ECFilledEllipseFileObserver* filledEllipseObserver = new ECFilledEllipseFileObserver(subj);
	ECCompositeFileObserver* compositeFileObserver = new ECCompositeFileObserver(subj);
}
ECFileHandler::~ECFileHandler() {}
void ECFileHandler::ImportShapeFile() {
	int lineNum = -1;
	std::ifstream importData;
	importData.open(filename);
	if (importData.is_open()) {
		std::string line;
		while (!importData.eof()) {
			lineNum++;
			std::getline(importData, line);
			if (line.size() == 0) continue;
			if (lineNum == 0) {
				continue;
			}
			std::vector<int> values;
			StringBreak(line, values);
			subj.SetLine(values);
			if (subj.GetShapeIsReady()) {
				model.AddShape(subj.PopShape());
			}
		}
	}
	importData.close();
}

void ECFileHandler::ExportShapeFile() {
	model.ClearSelectedShapes();
	model.BreakMultiSelect();
	std::vector<ECShape*> listShapes;
	for (int i = 1; i < model.GetNumShapes(); i++) {
		ECShape* shape = model.GetShapeAt(i);
		if (shape != NULL) {
			listShapes.push_back(shape);
		}
	}
	std::ofstream exportData;
	exportData.open(filename, std::ios::trunc);
	exportData << std::to_string(listShapes.size()) << std::endl;
	for (int i = 0; i < (int)listShapes.size() - 1; i++) {

		exportData << listShapes.at(i)->GetFileString();
	}
	if (listShapes.size() > 0) {
		std::string lastLine = listShapes.back()->GetFileString();
		for (int i = 0; i < (int)lastLine.size() - 1; i++) {
			exportData << lastLine[i];
		}
	}
	exportData.close();
}

void ECFileHandler::StringBreak(const std::string inStr, std::vector<int>& values) {
	values.clear();
	std::string temp;
	for (char c : inStr) {
		if ((c == '\n' || c == ' ') && temp.size() > 0) {
			values.push_back(stoi(temp));
			temp.clear();
		}
		temp += c;
	}
	if (temp.size() > 0) {
		values.push_back(stoi(temp));
	}
}