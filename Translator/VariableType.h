#pragma once

enum class VariableType
{
    UNDEFINED = 0xffffff,

    INTEGER = 0x001000,
    FLOAT64 = 0x002000,
    BOOLEAN = 0x003000,
    STRING = 0x004000,
    FLOAT = 0x005000,
    VOID = 0x006000,
};