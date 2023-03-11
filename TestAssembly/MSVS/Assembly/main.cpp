#include <SDKDDKVer.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>

#include "Function.h"

// External assembly functions we want to call from here
extern "C"
{
    void hello_world_win_asm();
};


int main()
{
    Cpp2Asm::Test();

    hello_world_win_asm();

    return 0;
}