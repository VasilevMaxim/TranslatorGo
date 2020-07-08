.586
.model flat, stdcall

include <\masm32\include\msvcrt.inc>
include <\masm32\include\kernel32.inc>
includelib <\masm32\lib\msvcrt.lib>
includelib <\masm32\lib\kernel32.lib>

data segment
   print_format db "%d", 0
   sqrt_result dd 0
   div_operand_1 dd 0
   div_operand_2 dd 0
data ends

text segment

   a0 = -4
   b0 = -8
   c0 = -12
   d0 = -16
   l0 = -20
   i0 = -24
   a1 = -28
   a2 = -4
   b1 = -8
   c1 = -12
   d1 = -16
printD PROC
   enter 0, 0
   mov eax, [ebp + 8]
   invoke crt_printf, offset print_format, eax
   leave
   ret 4
printD ENDP

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

__main:
   enter 28, 0
   push 1
   pop a0[ebp]
   push 10
   pop b0[ebp]
   push -39
   pop c0[ebp]
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
   push 2
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
   pop l0[ebp]
   push 0
   pop i0[ebp]
__loop_start_391863513627400:
   push i0[ebp]
   pop ecx
   push 3
   pop edx
   cmp ecx, edx
   jge _compare_not_equal391863513660500
   push 1
   jmp _compare_end391863513660500
_compare_not_equal391863513660500:
   push 0
_compare_end391863513660500:
   pop eax
   cmp eax, 0
   je __loop_end_391863513627400
   push 1
   pop a1[ebp]
   push a1[ebp]
   push c0[ebp]
   pop eax
   pop ebx
   add eax, ebx
   push eax
   pop a1[ebp]
__loop_aftereffects_391863513627400:
   push i0[ebp]
   push 1
   pop eax
   pop ebx
   add eax, ebx
   push eax
   pop i0[ebp]
   jmp __loop_start_391863513627400
__loop_end_391863513627400:
   mov eax, d0[ebp]
   push eax
   call sqrt
   mov d0[ebp], eax
   mov eax, d0[ebp]
   push eax
   call printD
   leave
   ret
end __main
__funcc:
   enter 16, 0
   push 1
   pop a2[ebp]
   push 10
   pop b1[ebp]
   push -39
   pop c1[ebp]
   push b1[ebp]
   push b1[ebp]
   pop eax
   pop ebx
   imul eax, ebx
   push eax
   push 4
   push a2[ebp]
   pop eax
   pop ebx
   imul eax, ebx
   push eax
   push c1[ebp]
   pop eax
   pop ebx
   imul eax, ebx
   push eax
   pop ebx
   pop eax
   sub eax, ebx
   push eax
   pop d1[ebp]
   leave
   ret
text ends
end __main
