#pragma once
#include <string>

namespace stc
{
    using std::string;

// HEADER
    const string AsmHeader = ".586\n"
        ".model flat, stdcall\n\n"
        "include <\\masm32\\include\\msvcrt.inc>\n"
        "include <\\masm32\\include\\kernel32.inc>\n"
        "includelib <\\masm32\\lib\\msvcrt.lib>\n"
        "includelib <\\masm32\\lib\\kernel32.lib>\n";

    const string PrintFormat_d = "   print_format db \"%d\", 0\n";
    const string SqrtResult = "   sqrt_result dd 0\n";

    const string print_d = "printD";
    const string sqrt = "sqrt";

// DATA
    const string dataBegin = "data segment\n";

    const string divOperands = "   div_operand_1 dd 0\n"
        "   div_operand_2 dd 0\n";

    const string dataEnd = "data ends\n";

// TEXT
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



    // functions

    const string ProcPrint_d = "printD PROC\n"
        "   enter 0, 0\n"
        "   mov eax, [ebp + 8]\n"
        "   invoke crt_printf, offset print_format, eax\n"
        "   leave\n"
        "   ret 4\n"
        "printD ENDP\n";

    const string ProcSqrt =
        "sqrt PROC\n"
        "   enter 0, 0\n"
        "   push ebx\n"
        "   push ecx\n"
        "   push edx\n"
        "   mov eax, [ebp + 8]\n"
        "   mov sqrt_result, eax\n"
        "   finit\n"
        "   fild sqrt_result\n"
        "   fsqrt\n"
        "   fist sqrt_result\n"
        "   mov eax, sqrt_result\n"
        "   pop ebx\n"
        "   pop ecx\n"
        "   pop edx\n"
        "   leave\n"
        "   ret 4\n"
        "sqrt ENDP\n";
}