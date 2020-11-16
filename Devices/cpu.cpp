#include "cpu.h"

CPU::CPU()
{
    memory = RAM(RAM_CAPACITY);
    data = Stack(STACK_CAPACITY);
    revert = Stack(STACK_CAPACITY);

    flags = 0;
    PC = 0;
    dataRamBegin = RAM_DATA_BEGIN;
}

bool CPU::work()
{
    if(PC < dataRamBegin)
    {
        runCommand();
        PC++;

        return true;
    }

    return false;
}

void CPU::reset()
{
    data.clear();
    revert.clear();
    memory.clear();
    flags = 0;
    PC = 0;
}

Stack *CPU::getStackData()
{
    return &data;
}

RAM *CPU::getRAM()
{
    return &memory;
}

Stack *CPU::getStackRevert()
{
    return &revert;
}

quint8 CPU::getPC() const
{
    return PC;
}

quint8 CPU::getFlags() const
{
    return flags;
}

void CPU::runCommand()
{
    quint32 word = memory.read(PC);

    curCom.operation = static_cast<CommandName>(word >> 16);
    curCom.operand = static_cast<quint16>(word & 0xFFFF);

    switch (curCom.operation) {
    case NOP:
        nopOp();
        break;
    case ADDS:
    case ADDL:
    case SUB:
    case MUX:
        calcOp();
        break;
    case SWAP:
    case DROP:
    case PUSHR:
    case POPR:
    case PUSHO:
    case PUSHM:
    case POPM:
        stackOp();
        break;
    case JZ:
    case JN:
    case JP:
    case JSO:
    case JMP:
        jumpOp();
        break;
    }

    flags = alu.readFlags() | data.readFlags();
}

void CPU::nopOp()
{

}

void CPU::calcOp()
{
    if(curCom.operation == ADDS)
    {
        quint16 a, b;
        a = data.pop();
        b = data.read();
        data.push(a+b);
    }
    else if(curCom.operation == ADDL)
    {
        quint32 a, b;

        a = static_cast<quint32>(data.pop() << 16) | data.pop();
        b = static_cast<quint32>(data.pop() << 16) | data.pop();

        quint32 res = alu.addL(a, b);

        data.push(res & 0xFFFF);
        data.push(res >> 16);

    }
    else if(curCom.operation == SUB)
    {
        quint16 a, b;

        b = data.pop();
        a = data.read();

        data.push(alu.sub(a, b));
    }
    else if(curCom.operation == MUX)
    {
        quint32 res = alu.mux(data.pop(), data.read());

        data.push(res & 0xFFFF);
        data.push(res >> 16);
    }
}

void CPU::stackOp()
{
    if(curCom.operation == SWAP)
    {
        quint16 tmp1 = data.pop();
        quint16 tmp2 = data.pop();

        data.push(tmp1);
        data.push(tmp2);
    }
    else if(curCom.operation == DROP)
    {
        data.drop();
    }
    else if(curCom.operation == PUSHR)
    {
        revert.push(data.pop());
    }
    else if(curCom.operation == POPR)
    {
        data.push(revert.pop());
    }
    else if(curCom.operation == PUSHO)
    {
        data.push(curCom.operand);
    }
    else if(curCom.operation == PUSHM)
    {
        data.push(static_cast<quint16>(memory.read(static_cast<quint8>(curCom.operand))));
    }
    else if(curCom.operation == POPM)
    {
        memory.write(static_cast<quint8>(curCom.operand), data.pop());
    }
}

void CPU::jumpOp()
{
    if(curCom.operation == JZ)
    {
        if(flags & ZERO) PC = static_cast<quint8>(curCom.operand);
    }
    else if(curCom.operation == JN)
    {
        if(flags & NEGATIVE) PC = static_cast<quint8>(curCom.operand);
    }
    else if(curCom.operation == JP)
    {
        if(!( (flags & NEGATIVE) | (flags & ZERO) )) PC = static_cast<quint8>(curCom.operand);
    }
    else if(curCom.operation == JSO)
    {
        if(flags & STACK_ONE) PC = static_cast<quint8>(curCom.operand);
    }
    else if(curCom.operation == JMP)
    {
        PC = static_cast<quint8>(curCom.operand);
    }
}

void CPU::init(const QVector<Command> *commands)
{
    for(quint8 i=0; i<commands->size() && i<dataRamBegin; i++)
    {
        Command command = commands->at(i);
        quint32 value = (static_cast<quint32>(command.operation) << 16) | command.operand;
        memory.write(i, value);
    }
}
