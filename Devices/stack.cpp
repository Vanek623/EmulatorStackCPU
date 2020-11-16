#include "stack.h"

Stack::Stack()
{
    capacity = STACK_CAPACITY;
    pointer = 0;
    flags = EMPTY;
}

Stack::Stack(const quint8 capacity)
{
    this->capacity = capacity;
    pointer = 0;
    flags = EMPTY;
}

quint16 Stack::read() const
{
    return data.at(pointer);
}

quint16 Stack::pop()
{
    decreasePtr();
    return read();
}

void Stack::drop()
{
    decreasePtr();
}

void Stack::push(const quint16 value)
{
    data[pointer] = value;
    increasePtr();
}

quint8 Stack::readFlags() const
{
    return flags;
}

QVector<quint16> *Stack::getData()
{
    return &data;
}

void Stack::clear()
{
    for(int i=0; i<capacity; i++) data[i] = 0;
}

void Stack::fillZero()
{
    for(int i=0; i<capacity; i++) data.append(0);
}

void Stack::increasePtr()
{
    if(pointer < capacity - 1) pointer++;

    flags = EMPTY;
    if(pointer == capacity - 1) flags |= STACK_OVERFLOW;
    else if(pointer == 1) flags |= STACK_ONE;
}

void Stack::decreasePtr()
{
    if(pointer > 0) pointer--;

    flags = EMPTY;
    if(pointer == 0) flags |= STACK_EMPTY;
    else if(pointer == 1) flags |= STACK_ONE;
}
