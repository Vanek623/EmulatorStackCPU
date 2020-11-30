#include "lexer.h"

Lexer::Lexer()
{

}

QVector<Token> *Lexer::parse(const QString &text)
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
                if(!word.isEmpty()) addToken(word, tokens);
                word = "";
                skip = true;
            }
        }

        if(!skip) word.append(sim);
        if(i == text.length() - 1 && !word.isEmpty()) addToken(word, tokens);
    }

    return &tokens;
}

void Lexer::addToken(const QString &word, QVector<Token> &lexemes)
{
    Token lexeme;
    lexeme.value = word;

    if(markInitLexeme.exactMatch(word))
    {
        lexeme.type = MARK_I;
        QString tmp = word;
        tmp.chop(1);
        lexeme.value = tmp;
    }
    else if(markUseLexeme.exactMatch(word)) lexeme.type = MARK_U;
    else if(commandLexeme.exactMatch(word)) lexeme.type = COMMAND;
    else if(operandLexeme.exactMatch(word))
    {
        lexeme.type = OPERAND;
        QString tmp = word;
        tmp.remove("0x");
        lexeme.value = tmp;
    }
    else lexeme.type = UNKNOWN;

    lexemes.append(lexeme);
}
