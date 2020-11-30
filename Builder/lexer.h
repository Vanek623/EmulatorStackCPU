#pragma once

#include <QMap>
#include <QVector>
#include <QRegExp>

#include "structs.h"

const QRegExp markInitLexeme = QRegExp(QString::fromUtf8("[G-Z]{1}[0-9]{1}:"));
const QRegExp markUseLexeme = QRegExp(QString::fromUtf8("[G-Z]{1}[0-9]{1}"));
const QRegExp commandLexeme = QRegExp(QString::fromUtf8("[A-Z]+"));
const QRegExp operandLexeme = QRegExp(QString::fromUtf8("0x[0-9A-F]+"));

class Lexer
{
private:
    QVector<Token> tokens;
public:
    Lexer();

    QVector<Token> *parse(const QString &text);

private:
    void addToken(const QString &word, QVector<Token> &tokens);
};

