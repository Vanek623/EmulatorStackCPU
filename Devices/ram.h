#pragma once

#include <QVector>

class RAM
{
private:
    QVector<quint32> data;
    quint8 capacity;

public:
    RAM();
    RAM(const quint8 capacity);

    void write(const quint8 address, const quint32 value);
    quint32 read(const quint8 address) const;

    void clear();

    QVector<quint32> *getData() const;
    quint8 size() const;

private:
    void fillData(const quint32 value);
};
