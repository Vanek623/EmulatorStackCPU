#include "cpu.h"

CPU::CPU()
{
    flags = 0;
    PC = 0;
    dataRamBegin = memory.size()/2;
}

bool CPU::work()
{
    if(PC < 0xFF)
    {


        return true;
    }

    return false;
}

void CPU::runCommand()
{

}

void CPU::init(const QVector<Command> *commands)
{
    for(quint8 i=0; i<commands->size() && i<dataRamBegin; i++)
    {
        Command command = commands->at(i);
        quint32 value = static_cast<quint32>(command.operation) << 16 | command.operand;
        memory.write(i, value);
    }
}
