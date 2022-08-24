.code
RandomGenerator proc
	rdrand	eax
	ret
RandomGenerator endp

__AsmImpossibleDisassm proc
	push rax

	mov ax, 05EBh	; db 066h, 0B8h, 0EBh, 005h
	xor eax, eax	; db 033h, 0C0h
	db 074h, 0fah
	db 0e8h			; call

	pop rax
	ret
__AsmImpossibleDisassm endp


__AsmJmpSameTarget proc
	jz L_END
	jnz L_END
	db 0e8h
L_END:
	nop
	ret
__AsmJmpSameTarget endp
end