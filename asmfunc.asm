; asmfunc.asm

section .text
bits 64
default rel
global compute_acceleration

compute_acceleration:
    ; rcx = float* matrix
    ; rdx = int rows
    ; r8  = int* output

    push rbx             ; save callee-saved register

    xor r9, r9           ; row index = 0

.loop:
    cmp r9, rdx
    jge .done            ; exit if r9 >= rows

    ; offset = r9 * 12 (3 floats per row, 4 bytes each)
    mov r10, r9
    imul r10, r10, 12

    ; Vi = [matrix + offset]
    movss xmm1, [rcx + r10]
    ; Vf = [matrix + offset + 4]
    movss xmm2, [rcx + r10 + 4]
    ; T  = [matrix + offset + 8]
    movss xmm3, [rcx + r10 + 8]

    ; Vi_mps = Vi * factor
    movss xmm4, xmm1
    mulss xmm4, [rel factor]

    ; Vf_mps = Vf * factor
    movss xmm5, xmm2
    mulss xmm5, [rel factor]

    ; accel = (Vf_mps - Vi_mps) / T
    subss xmm5, xmm4
    divss xmm5, xmm3

    ; int accel = (int)accel
    cvtss2si eax, xmm5

    ; output[r9] = accel
    mov [r8 + r9 * 4], eax

    inc r9
    jmp .loop

.done:
    pop rbx
    ret

section .data
factor: dd 0.27777778    ; conversion from km/h to m/s
