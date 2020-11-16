#pragma once

#include <QVector>

#include "flags.h"
#include "consts.h"

class Stack
{
private:
    QVector<quint16> data;
    quint8 capacity;
    quint8 pointer;
    quint8 flags;

public:
    Stack();
    Stack(const quint8 capacity);

    quint16 read() const;
    quint16 pop();

    void drop();
    void push(const quint16 value);

    quint8 readFlags() const;
    QVector<quint16> *getData();

    void clear();

private:
    void fillZero();

    void increasePtr();
    void decreasePtr();
};
