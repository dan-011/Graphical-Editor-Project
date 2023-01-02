#ifndef __ECCOMMAND_H
#define __ECCOMMAND_H

#include <vector>

//************************************************************************************************************
// ECCommandHistory
class ECCommand
{
public:
    virtual ~ECCommand() {}
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;
};

//************************************************************************************************************
// ECCommandHistory
class ECCommandHistory
{
public:
    ECCommandHistory();
    ECCommandHistory(const ECCommandHistory& rhs) = delete;
    ECCommandHistory(ECCommandHistory&& rhs) noexcept;
    virtual ~ECCommandHistory();
    ECCommandHistory& operator=(const ECCommandHistory& rhs) = delete;
    ECCommandHistory& operator=(ECCommandHistory&& rhs) noexcept;
    bool Undo();
    bool Redo();
    void ExecuteCmd(ECCommand* pCmd);

private:
    std::vector<ECCommand*> history;
    int pos;
    int length;
};

#endif