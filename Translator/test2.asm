text segment

__main:
   enter 20, 0
   a = -4
   b = -8
   c = -12
   d = -16
   l = -20
   push 1
   pop a[ebp]
   push 10
   pop b[ebp]
   push -39
   pop c[ebp]
   push b[ebp]
   push b[ebp]
   pop eax
   pop ebx
   imul eax, ebx
   push eax
   push 4
   push a[ebp]
   pop eax
   pop ebx
   imul eax, ebx
   push eax
   push c[ebp]
   pop eax
   pop ebx
   imul eax, ebx
   push eax
   pop ebx
   pop eax
   sub eax, ebx
   push eax
   pop d[ebp]
   push d[ebp]
   push 2
   pop ebx
   pop eax
   pop l[ebp]
__loop_start_326869961759600:
__loop_aftereffects_326869961759600:
   push l[ebp]
   push l[ebp]
   pop eax
   pop ebx
   imul eax, ebx
   push eax
   pop ecx
   push d[ebp]
   pop edx
   cmp ecx, edx
   je _compare_not_equal326869961788200
   push 1
   jmp _compare_end326869961788200
_compare_not_equal326869961788200:
   push 0
_compare_end326869961788200:
   pop eax
   cmp eax, 0
   je __loop_end_326869961759600
   push l[ebp]
   push 1
   pop ebx
   pop eax
   sub eax, ebx
   push eax
   pop l[ebp]
   jmp __loop_start_326869961759600
__loop_end_326869961759600:
   leave
   ret
text ends
end __main
