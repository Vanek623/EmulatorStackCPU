#include "ram.h"

RAM::RAM()
{
    capacity = 32;
    fillData(0);
}

RAM::RAM(const quint8 capacity)
{
    this->capacity = capacity;
    fillData(0);
}

void RAM::fillData(const quint32 value)
{
    for(int i=0; i<capacity; i++)
        data.append(value);
}

void RAM::write(const quint8 address, const quint32 value)
{
    if(address < capacity) data[address] = value;
}

quint32 RAM::read(const quint8 address) const
{
    if(address < capacity) return data[address];
    else return 0;
}

void RAM::clear()
{
    for(int i=0; i<capacity; i++) data[i] = 0;
}

QVector<quint32> *RAM::getData() const
{
    return &data;
}

quint8 RAM::size() const
{
    return capacity;
}
