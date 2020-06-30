#pragma once
#include <string>

namespace stc
{
    using std::string;

    const string AsmHeader = ".586\n"
        ".model flat, stdcall\n\n"
        "include <\\masm32\\include\\msvcrt.inc>\n"
        "include <\\masm32\\include\\kernel32.inc>\n"
        "includelib <\\masm32\\lib\\msvcrt.lib>\n"
        "includelib <\\masm32\\lib\\kernel32.lib>\n";

    const string dataBegin = "data segment\n";
    const string dataEnd = "data ends\n";

    const string textBegin = "text segment\n";
    const string textEnd = "text ends\n";

    const string mainBegin = "__main:\n";
    const string mainEnd = "end __main\n";

    const string functionProlog = "   enter ";

    const string functionEpilogue = "   leave\n";

    const string functionReturn = "   ret\n";

    const string program_exit = "   push 0\n"
        "   call ExitProcess\n";

    const string tab = "   ";



    // registers
    const string eax("eax");
    const string ebx("ebx");
    const string ecx("ecx");
    const string edx("edx");
    const string esi("esi");
    const string edi("edi");



    const string null("0");
    const string one("1");
    const string minus_one("-1");
}