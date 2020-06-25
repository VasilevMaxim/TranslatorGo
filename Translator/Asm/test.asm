.586
.model flat, stdcall

include <\masm32\include\msvcrt.inc>
include <\masm32\include\kernel32.inc>
includelib <\masm32\lib\msvcrt.lib>
includelib <\masm32\lib\kernel32.lib>

data segment
   println_format db "%s", 0
   hello_world db "Hfello World", 0
data ends

text segment



print PROC
   enter 0, 0
   mov eax, [ebp + 8]
   invoke crt_printf, offset println_format, eax
   leave
   ret 4
print ENDP


__start:

   enter 0, 0
  
   push offset hello_world
   call print

   leave

   ret

text ends

end __start

