#pragma once

#include "alu.h"
#include "ram.h"
#include "stack.h"

#include "command.h"

class CPU
{
private:
    ALU alu;
    RAM memory;
    Stack data;
    Stack revert;

    quint8 flags;
    quint8 PC;

    quint8 dataRamBegin;

    Command curCom;

public:
    CPU();

    void init(const QVector<Command> *commands);
    bool work();
    void reset();

    QVector<quint16> *getStackData() const;
    QVector<quint32> *getMemData() const;
    QVector<quint16> *getStackRevert() const;

    quint8 getPC() const;
    quint8 getFlags() const;

private:
    void runCommand();

    void nopOp();
    void calcOp();
    void stackOp();
    void jumpOp();

};
