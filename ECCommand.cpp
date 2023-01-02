#include "ECCommand.h"

//************************************************************************************************************
// ECCommandHistory
ECCommandHistory::ECCommandHistory() : pos(0), length(0) {}
ECCommandHistory::ECCommandHistory(ECCommandHistory&& rhs) noexcept {
    pos = rhs.pos;
    length = rhs.length;
    for (int i = 0; i < (int)rhs.history.size(); i++) {
        history.push_back(rhs.history[i]);
        rhs.history[i] = NULL;
    }
}

ECCommandHistory :: ~ECCommandHistory()
{
    for (ECCommand* command : history) {
        delete command;
    }
}

ECCommandHistory& ECCommandHistory::operator=(ECCommandHistory&& rhs) noexcept {
    pos = rhs.pos;
    length = rhs.length;

    for (int i = 0; i < (int)rhs.history.size(); i++) {
        history.push_back(rhs.history[i]);
        rhs.history[i] = NULL;
    }
    rhs.history.clear();
    return *this;
}

bool ECCommandHistory::Undo() {
    if (length == 0) return false;
    if (pos == 0) {
        return false;
    }
    pos--;
    history[pos]->UnExecute();
    return true;
}

bool ECCommandHistory::Redo() {
    if (pos >= length) return false;
    history[pos]->Execute();
    pos++;
    return true;
}

void ECCommandHistory::ExecuteCmd(ECCommand* pCmd) {
    pCmd->Execute();
    pos++;
    if (pos > (int)history.size()) {
        history.push_back(pCmd);
        length++;
    }
    else {
        int curCmdIndex = pos - 1;
        ECCommand* ptr = history[curCmdIndex];
        history[curCmdIndex] = pCmd;
        length = pos;
        delete ptr;
    }
}