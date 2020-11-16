#pragma once

#include <QMap>
#include <QVector>
#include <QRegExp>

#include "structs.h"

const QRegExp markInitExp = QRegExp(QString::fromUtf8("[G-Z]{1}[0-9]{1}:"));
const QRegExp markUseExp = QRegExp(QString::fromUtf8("[G-Z]{1}[0-9]{1}"));
const QRegExp commandExp = QRegExp(QString::fromUtf8("[A-Z]+"));
const QRegExp operandExp = QRegExp(QString::fromUtf8("0x[0-9A-F]+"));

class Lexer
{
private:
    QVector<Lexeme> lexemes;
public:
    Lexer();

    QVector<Lexeme> *parse(const QString &text);

private:
    void addLexeme(const QString &word, QVector<Lexeme> &lexemes);
};

