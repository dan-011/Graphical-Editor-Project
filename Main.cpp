#include "ECGraphicViewImp.h"
#include "ECModel.h"
#include "ECIndivObservers.h"
#include "ECFileHandler.h"
#include <iostream>

int real_main(int argc, char** argv)
{
    const int widthWin = 1000, heightWin = 800;
    ECGraphicViewImp view(widthWin, heightWin);
    ECModel model(view);
    ECFileHandler* fileHandler = NULL;
    if (argc > 1) {
        fileHandler = new ECFileHandler(model, argv[1]);
        fileHandler->ImportShapeFile();
    }
    ECDeleteShapeObserver deleteShapeObserver(view, model);
    ECCtrlKeyDownObserver ctrlKeyDownObserver(view, model);
    ECModeChangeObserver modeChangeObserver(view, model);
    ECCtrlKeyUpObserver ctrlKeyUpObserver(view, model);
    ECMouseDownObserver mouseDownObserver(view, model);
    ECDraggingObserver draggingObserver(view, model);
    ECRightKeyObserver rightKeyObserver(view, model);
    ECMouseUpObserver mouseUpObserver(view, model);
    ECLeftKeyObserver leftKeyObserver(view, model);
    ECDownKeyObserver downKeyObserver(view, model);
    ECUpKeyObserver upKeyObserver(view, model);
    ECTimerObserver timerObserver(view, model);
    ECUndoObserver undoObserver(view, model);
    ECRedoObserver redoObserver(view, model);
    ECGKeyObserver gKeyObserver(view, model);
    ECFKeyObserver fKeyObserver(view, model);

    try {
        view.Show();
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
    }
    if (fileHandler != NULL) {
        fileHandler->ExportShapeFile();
    }
    delete fileHandler;
    return 0;
}

int main(int argc, char** argv) {
    return real_main(argc, argv);
}