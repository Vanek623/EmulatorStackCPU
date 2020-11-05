#pragma once

#include <QtGlobal>

#include "flags.h"

class ALU
{
private:
    quint8 flags;

public:
    ALU();

    quint16 add(const quint16 a, const quint16 b);
    quint32 addL(const quint32 a, const quint32 b);
    quint16 sub(const quint16 a, const quint16 b);
    quint32 mux(const quint16 a, const quint16 b);

    quint8 readFlags() const;
};
