.syntax unified
.cpu arm7tdmi
.thumb
.section .text
.balign 4
.global ProbeEntry
.global ProbeObservedHit

/* Site inputs are r6 (resolved target) and r5 (new HP).
 * The probe only provides a trace marker; it does not reserve game RAM. */
.thumb_func
ProbeEntry:
    push {r0-r4}
    ldr r0, =0x02002192
    ldrh r0, [r0]
    cmp r0, #6
    bne Continue
    ldr r0, =0x020034ec
    cmp r6, r0
    bne Continue
    ldrb r0, [r6, #4]
    cmp r0, #16
    bne Continue
    ldrh r0, [r6, #24]
    cmp r5, r0
    bhs Continue
    ldr r0, =0x0200f4a8
    ldr r0, [r0]
    cmp r0, #0
    beq Continue
    adds r0, #220
    ldrh r0, [r0]
    cmp r0, #57
    bne Continue
ProbeObservedHit:
    mov r8, r8
Continue:
    pop {r0-r4}
    strh r5, [r6, #24]
    adds r0, r6, #0
    ldr r2, =0x080a22a1
    mov lr, r2
    ldr r2, =0x080c8281
    bx r2
.ltorg
