#pragma once

#include <QtGlobal>
#include <QString>

enum CommandName{
    NOP,    //Бездействие

    //Арифметика
    ADDS,   //Сложение двух 16х чисел
    ADDL,   //Сложение двух 32х чисел
    SUB,    //Вычитание двух 16х чисел (из второго вычитается первое)
    MUX,    //Умножение двух 16х чисел
    DEC,    //Уменьшение вершины стека на 1
    INC,    //Увеличение вершины стека на 1

    //Работа со стеком
    SWAP,   //Замена двух чисел в стеке
    DROP,   //Удаление элемента вершины стека
    PUSHR,  //Перемещение вершины стека данных в стек возвратов
    POPR,   //Перемещение веришны стека возвратов в стек данных
    COPY,
    PUSHM,  //Загрузка в стек из ОЗУ по адресу вершины стека
    POPM,   //Загрузка в ОЗУ подвершины стека по адресу вершины стека

    //Операции с указанием  непосредственного операнда (НО)
    PUSHO,  //Загрузка в стек 16х числа

    //Операции с указанием НО или метки
    JZ,     //Переход к заданной строке при флаге нуля Z
    JN,     //Переход к заданной строке при флаге отрицательности N
    JP,     //Переход к заданной строке при флаге отсутсвии флагов Z и N
    JSO,    //Переход к заданной строке при флаге одного элемента в стеке (SO)
    JSE,    //Переход к заданной строке при флаге отсутствия элементов в стеке (SЕ)
    JMP     //Переход к заданной строке
};

struct Command
{
    CommandName operation;
    quint16 operand;
};

enum TokenType{
    COMMAND,
    OPERAND,
    MARK_I,
    MARK_U,
    UNKNOWN
};

struct Token
{
    TokenType type;
    QString value;
};
