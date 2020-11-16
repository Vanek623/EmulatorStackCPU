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
    POPM,

    JZ,
    JN,
    JP,
    JSO,
    JMP
};

struct Command
{
    CommandNames operation;
    quint16 operand;
};
