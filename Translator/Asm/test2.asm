.586
.model flat, stdcall

include <\masm32\include\msvcrt.inc>
include <\masm32\include\kernel32.inc>
includelib <\masm32\lib\msvcrt.lib>
includelib <\masm32\lib\kernel32.lib>

data segment
   printd_format db "%d", 0
   prints_format db "%s", 0
   input_format db "%d", 0
   input_result dd 0
   sqrt_result dd 0
   div_operand_1 dd 0
   div_operand_2 dd 0
   string_const_0 db "x^2", 0
   string_const_1 db " + ", 0
   string_const_2 db "x", 0
   string_const_3 db " + ", 0
   string_const_4 db " = 0;  ", 13,10,0
   string_const_5 db "The discriminant < 0 ! ", 13,10,0
   string_const_6 db "x = ", 0
   string_const_7 db "x1 = ", 0
   string_const_8 db " ", 13,10,0
   string_const_9 db "x2 = ", 0
data ends

text segment

   n0 = -4
   x0 = -8
   d0 = -4
   x1 = -8
   x10 = -12
   x20 = -16
   c0 = 8
   b0 = 12
   a0 = 16

printD PROC
   enter 0, 0
   mov eax, [ebp + 8]
   invoke crt_printf, offset printd_format, eax
   leave
   ret 4
printD ENDP

printS PROC
   enter 0, 0
   push eax
   push ebx
   push ecx
   push edx
   mov eax, [ebp + 8]
   invoke crt_printf, offset prints_format, eax
   pop eax
   pop ebx
   pop ecx
   pop edx
   leave
   ret 4
printS ENDP

sqrt PROC
   enter 0, 0
   push ebx
   push ecx
   push edx
   mov eax, [ebp + 8]
   mov sqrt_result, eax
   finit
   fild sqrt_result
   fsqrt
   fist sqrt_result
   mov eax, sqrt_result
   pop ebx
   pop ecx
   pop edx
   leave
   ret 4
sqrt ENDP

input PROC
   enter 16, 0
   push ebx
   push ecx
   push edx
   invoke crt_scanf, offset input_format, offset input_result
   mov eax, input_result
   pop ebx
   pop ecx
   pop edx
   leave
   ret 
input ENDP

SqrEq PROC
   enter 16, 0
   mov eax, a0[ebp]
   push eax
   call printD
   push offset string_const_0
   call printS
   push offset string_const_3
   call printS
   mov eax, b0[ebp]
   push eax
   call printD
   push offset string_const_2
   call printS
   push offset string_const_3
   call printS
   mov eax, c0[ebp]
   push eax
   call printD
   push offset string_const_4
   call printS
   push b0[ebp]
   push b0[ebp]
   pop eax
   pop ebx
   imul eax, ebx
   push eax
   push 4
   push a0[ebp]
   pop eax
   pop ebx
   imul eax, ebx
   push eax
   push c0[ebp]
   pop eax
   pop ebx
   imul eax, ebx
   push eax
   pop ebx
   pop eax
   sub eax, ebx
   push eax
   pop d0[ebp]
   push d0[ebp]
   pop ecx
   push 0
   pop edx
   cmp ecx, edx
   jge _compare_not_equal482253299669100
   push 1
   jmp _compare_end482253299669100
_compare_not_equal482253299669100:
   push 0
_compare_end482253299669100:
   pop eax
   cmp eax, 0
   je __if_else_482253299652800
__if_start_482253299652800:
   push offset string_const_5
   call printS
   jmp __if_end_482253299652800
__if_else_482253299652800:
   push d0[ebp]
   pop ecx
   push 0
   pop edx
   cmp ecx, edx
   jne _compare_not_equal482253299823600
   push 1
   jmp _compare_end482253299823600
_compare_not_equal482253299823600:
   push 0
_compare_end482253299823600:
   pop eax
   cmp eax, 0
   je __if_else_482253299813600
__if_start_482253299813600:
   mov eax, d0[ebp]
   push eax
   call sqrt
   mov d0[ebp], eax
   push 0
   push b0[ebp]
   push 2
   push a0[ebp]
   pop eax
   pop ebx
   imul eax, ebx
   push eax
   pop ebx
   pop eax
   mov div_operand_1, eax
   mov div_operand_2, ebx
   finit
   fild div_operand_2
   fild div_operand_1
   fdiv st(0), st(1)
   fist div_operand_1
   push div_operand_1
   pop ebx
   pop eax
   sub eax, ebx
   push eax
   pop x1[ebp]
   push offset string_const_6
   call printS
   mov eax, x1[ebp]
   push eax
   call printD
   jmp __if_end_482253299813600
__if_else_482253299813600:
__if_start_482253300228800:
   mov eax, d0[ebp]
   push eax
   call sqrt
   mov d0[ebp], eax
   push 0
   push b0[ebp]
   pop ebx
   pop eax
   sub eax, ebx
   push eax
   push d0[ebp]
   pop eax
   pop ebx
   add eax, ebx
   push eax
   push 2
   push a0[ebp]
   pop eax
   pop ebx
   imul eax, ebx
   push eax
   pop ebx
   pop eax
   mov div_operand_1, eax
   mov div_operand_2, ebx
   finit
   fild div_operand_2
   fild div_operand_1
   fdiv st(0), st(1)
   fist div_operand_1
   push div_operand_1
   pop x10[ebp]
   push 0
   push b0[ebp]
   pop ebx
   pop eax
   sub eax, ebx
   push eax
   push d0[ebp]
   pop ebx
   pop eax
   sub eax, ebx
   push eax
   push 2
   push a0[ebp]
   pop eax
   pop ebx
   imul eax, ebx
   push eax
   pop ebx
   pop eax
   mov div_operand_1, eax
   mov div_operand_2, ebx
   finit
   fild div_operand_2
   fild div_operand_1
   fdiv st(0), st(1)
   fist div_operand_1
   push div_operand_1
   pop x20[ebp]
   push offset string_const_7
   call printS
   mov eax, x10[ebp]
   push eax
   call printD
   push offset string_const_8
   call printS
   push offset string_const_9
   call printS
   mov eax, x20[ebp]
   push eax
   call printD
   jmp __if_end_482253300228800
__if_else_482253300228800:
__if_end_482253300228800:
__if_end_482253299813600:
__if_end_482253299652800:
   push 2
   pop eax
   leave
   ret 12
SqrEq ENDP

__main:
   enter 8, 0
   push 3
   pop n0[ebp]

   push 2
   push 3
   push 5
   call SqrEq
   push eax
   pop x0[ebp]
   leave
   ret
text ends
end __main
