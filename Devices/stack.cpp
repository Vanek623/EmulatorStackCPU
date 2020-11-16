#include "stack.h"

Stack::Stack()
{
    capacity = STACK_CAPACITY;
    pointer = 0;
    flags = STACK_EMPTY;
    stack = QVector<quint16>(capacity);
}

Stack::Stack(const quint8 capacity)
{
    this->capacity = capacity;
    pointer = 0;
    flags = STACK_EMPTY;
    stack = QVector<quint16>(capacity);
}

quint16 Stack::read()
{
    if(flags & STACK_EMPTY) return 0;
    return stack.at(pointer);
}

quint16 Stack::pop()
{
    quint16 value = read();
    decreasePtr();

    return value;
}

void Stack::drop()
{
    if(flags & STACK_EMPTY) return;
    decreasePtr();
}

void Stack::push(const quint16 value)
{
    increasePtr();

    if(flags & STACK_OVERFLOW) return;

    stack[pointer] = value;
}

quint8 Stack::readFlags() const
{
    return flags;
}

QVector<quint16> *Stack::getData()
{
    return &stack;
}

quint8 Stack::getPointer()
{
    return pointer;
}

bool Stack::isEmpty()
{
    return flags & STACK_EMPTY;
}

void Stack::clear()
{
    if(stack.isEmpty()) return;
    for(int i=0; i<capacity; i++) stack[i] = 0;

    pointer = 0;
    flags = STACK_EMPTY;
}

void Stack::fillZero()
{
    for(int i=0; i<capacity; i++) stack.append(0);
}

void Stack::increasePtr()
{
    bool hasPlace = pointer < capacity - 1;
    bool isEmpty = (flags & STACK_EMPTY) > 0;

    if(hasPlace && !isEmpty)
    {
        flags = NONE;
        pointer++;
    }
    else if(hasPlace && isEmpty)
    {
        flags = STACK_ONE;
    }
    else if(!hasPlace)
    {
        flags = STACK_OVERFLOW;
    }
}

void Stack::decreasePtr()
{
    bool isEmpty = (flags & STACK_EMPTY) > 0;

    if(isEmpty)
    {
        return;
    }
    else if(pointer == 0 && !isEmpty)
    {
        flags = STACK_EMPTY;
    }
    else
    {
        flags = pointer == 1 ? STACK_ONE : NONE;
        pointer--;
    }
}
