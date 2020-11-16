#include "builder.h"

Builder::Builder()
{}

int Builder::compile(const QString &programTxt)
{
    Lexer lexer;

    //parse text to lexemes
    QVector<Lexeme> *lexemes = lexer.parse(programTxt);

    //find mark initialize
    quint16 lineCount = 0;
    for(int i=0; i<lexemes->size(); i++)
    {
        Lexeme lexeme = lexemes->at(i);
        if(lexeme.type == MARK_I) marks.insert(lexeme.value, lineCount - 1);
        else if(lexeme.type == COMMAND) lineCount++;
    }

    setupCommandList();

    return parse(lexemes);
}

QVector<Command> *Builder::getCompiledProgramm()
{
    return &commands;
}

//initialize list of commands and it's signature
void Builder::setupCommandList()
{
    Command commandPattern;
    QStringList list;

    list<<"NOP"<<"ADDS"<<"ADDL"<<"SUB"<<"MUX"<<"DEC"<<"INC"<<"SWAP"<<"DROP"<<"PUSHR"
        <<"POPR"<< "COPY"<<"PUSHM"<<"POPM"<<"PUSHO"<<"JZ"<<"JN"<<"JP"<<"JSO"<<"JSE"<<"JMP";

    for(int i=0; i<list.size(); i++)
    {
        commandPattern.operation = static_cast<CommandName>(i);

        if(commandPattern.operation >= PUSHO) commandPattern.operand = 1;
        else commandPattern.operand = 0;

        commandList.insert(list.at(i), commandPattern);
    }
}
int Builder::parse(const QVector<Lexeme> *lexemes)
{
    int lineCount = 0;
    QVector<Lexeme>::const_iterator it;
    for(it = lexemes->begin(); it != lexemes->end(); ++it)
    {
        Lexeme lexeme = *it;

        // if this lexeme is a mark initializer, increase counter
        if(lexeme.type == MARK_I)
        {
            lineCount++;
            continue;
        }
        //else if this lexeme is a command and next lexeme mark or operand, initialize command
        else if(lexeme.type == COMMAND && commandList.contains(lexeme.value))
        {
            Command commandPattern = commandList.value(lexeme.value);

            if(commandPattern.operand == 1 && it + 1 != lexemes->end())
            {
                Lexeme operand = *(++it);

                if(operand.type == OPERAND)
                {
                    commandPattern.operand = operand.value.toUShort(nullptr, 16);
                }
                else if(operand.type == MARK_U && marks.contains(operand.value))
                {
                    commandPattern.operand = marks.value(operand.value);
                }
                else return lineCount;

            }
            else if(commandPattern.operand != 0) return lineCount;

            commands.append(commandPattern);
            lineCount++;
        }
        else return lineCount;
    }

    return -1;
}
