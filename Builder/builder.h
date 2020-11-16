#pragma once

#include "lexer.h"

class Builder
{
private:
    QVector<Command> commands;
    QMap<QString, quint16> marks;
    QMap<QString, Command> commandList;

public:
    Builder();

    int compile(const QString &programTxt);
    QVector<Command> *getCompiledProgramm();

private:
    void setupCommandList();
    int parse(const QVector<Lexeme> *lexemes);
};
