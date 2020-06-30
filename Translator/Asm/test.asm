.586
.model flat, stdcall

include <\masm32\include\msvcrt.inc>
include <\masm32\include\kernel32.inc>
includelib <\masm32\lib\msvcrt.lib>
includelib <\masm32\lib\kernel32.lib>

data segment
   print_format db "%d", 0
data ends

text segment



print PROC
   enter 0, 0
   mov eax, [ebp + 8]
   invoke crt_printf, offset print_format, eax
   leave
   ret 4
print ENDP


tests PROC
   enter 8, 0
   
   push 2
   push 3
   
   pop eax
   add eax, 2

   
   leave
   ret
tests ENDP

__start:

   enter 0, 0
   
   call tests
   
   push eax
   call print

   leave
   ret

text ends

end __start

