.data
extern PA : qword
.code
runASM proc
jmp qword ptr [PA]
runASM endp
end
