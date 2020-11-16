#pragma once

enum Flags
{
    NONE = 0,

    NEGATIVE = 1,
    ZERO = 2,
    CARRY = 4,

    STACK_EMPTY = 8,
    STACK_ONE = 16,
    STACK_OVERFLOW = 32
};
