#include "lexer.h"

Lexer::Lexer()
{

}

QVector<Lexeme> *Lexer::parse(const QString &text)
{
    const QString brakes = " \n:";
    QString word = "";

    for(int i=0; i<text.length(); i++)
    {
        QChar sim = text.at(i);
        bool skip = false;

        for(int j=0; j<brakes.length(); j++)
        {
            if(sim == brakes.at(j))
            {
                if(j == 2) word.append(sim);
                if(!word.isEmpty()) addLexeme(word, lexemes);
                word = "";
                skip = true;
            }
        }

        if(!skip) word.append(sim);
        if(i == text.length() - 1 && !word.isEmpty()) addLexeme(word, lexemes);
    }

    return &lexemes;
}

void Lexer::addLexeme(const QString &word, QVector<Lexeme> &lexemes)
{
    Lexeme lexeme;
    lexeme.value = word;

    if(markInitExp.exactMatch(word))
    {
        lexeme.type = MARK_I;
        QString tmp = word;
        tmp.chop(1);
        lexeme.value = tmp;
    }
    else if(markUseExp.exactMatch(word)) lexeme.type = MARK_U;
    else if(commandExp.exactMatch(word)) lexeme.type = COMMAND;
    else if(operandExp.exactMatch(word))
    {
        lexeme.type = OPERAND;
        QString tmp = word;
        tmp.remove("0x");
        lexeme.value = tmp;
    }
    else lexeme.type = UNKNOWN;

    lexemes.append(lexeme);
}
