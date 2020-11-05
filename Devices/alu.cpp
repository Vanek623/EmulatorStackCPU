#include "alu.h"

ALU::ALU()
{
    flags = EMPTY;
}

quint16 ALU::add(const quint16 a, const quint16 b)
{
    quint32 result = a + b;
    flags = EMPTY;

    if(result & 0x10000) flags |= CARRY;
    if(reuslt == 0) flags |= ZERO;

    return static_cast<quint16>(result);
}

quint32 ALU::addL(const quint32 a, const quint32 b)
{
    quint64 result = a + b;
    flags = EMPTY;

    if(result & 0x100000000) flags |= CARRY;
    if(result == 0) flags |= ZERO;

    return static_cast<quint32>(result);
}

quint16 ALU::sub(const quint16 a, const quint16 b)
{
    int result = a - b;
    flags = EMPTY;

    if(result < 0) flags |= NEGATIVE;
    if(result == 0) flags |= ZERO;

    return static_cast<quint16>(a - b);
}

quint8 ALU::readFlags() const
{
    return flags;
}
