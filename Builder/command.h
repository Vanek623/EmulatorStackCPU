#pragma once

#include <QtGlobal>

enum CommandNames
{
    NOP,
    ADD,
    ADDL,
    SUB,
    MUX,
    SWAP,
    DROP,
    PUSHR,
    POPR,
    //has operand
    PUSH,
    PUSHM,
    POP,
    JZ,
    JN,
    JSO,
    JMP
};

struct Command
{
    CommandNames operation;
    quint16 operand;
};
