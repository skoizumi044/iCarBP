; @file Mcu_Asm.S
; @brief MCU共通のアセンブラによる処理を提供する
; @author KSEII T.Terazawa, K.Kato
; @copyright 2020 Kernel Software Engineering

 .list
 .section .text

.global _Mcu_GetPSW
_Mcu_GetPSW:
    MVFC   PSW, R1
    RTS


.global _Mcu_InterlockedExchange
_Mcu_InterlockedExchange:
    XCHG  [R1], R2
    MOV    R2, R1
    RTS

.global _Mcu_SFR_WriteBit
_Mcu_SFR_WriteBit:
    TST r3, r3      ; r3 & r3
    BEQ 1f          ; 0 ?
    NOP             ; cycle合わせ
    NOP             ; cycle合わせ
    NOP             ; cycle合わせ
    NOP             ; cycle合わせ

    BSET r2, [r1]   ; bit set
    RTS             ; rts

1:
    BCLR r2, [r1]
    RTS             ; rts

.text
.end
