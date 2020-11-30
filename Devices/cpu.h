#pragma once

#include "alu.h"
#include "ram.h"
#include "stack.h"

#include "structs.h"

class CPU
{
private:
    ALU alu;
    RAM dataMem;
    RAM progMem;
    Stack data;
    Stack revert;

    quint8 flags;
    quint8 PC;

    Command curCom;

public:
    CPU();

    void init(const QVector<Command> *commands);
    bool work();
    void reset();

    Stack *getStackData();
    RAM *getDataRAM();
    RAM *getProgRAM();
    Stack *getStackRevert();

    quint8 getPC() const;
    quint8 getFlags() const;

private:
    void runCommand();

    void nopOp();
    void calcOp();
    void stackOp();
    void jumpOp();

};
