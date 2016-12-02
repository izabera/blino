// small asm language for a small virtual machine

// instructions are 2 bytes long, + 0/1/2 args
//
// 1st byte:
// 00000000
// ^        1 if 1st arg 16 bit, 0 otherwise
//  ^       1 if 2nd arg...
//   ^^^^^^ instr code
//
// 2nd byte:
// 00000000
// ^^       0 if 1st arg is immediate,
//          1 if %reg,
//          2 if (imm),
//          3 if (%reg)
//   ^^     same for 2nd arg
//     ^^^^ unused as of now
//
// 1st arg is src, 2nd is dest

// valid instructions:
enum instr {
  ADD     =  0, // add     arg arg
  ADC     =  1, // adc     arg arg
  SUB     =  2, // sub     arg arg
  MUL     =  3, // mul     arg arg    -- unsigned
  DIV     =  4, // div     arg arg
  IMUL    =  5, // imul    arg arg    -- signed
  IDIV    =  6, // idiv    arg arg

  NOT     =  7, // not     arg
  OR      =  8, // or      arg arg
  AND     =  9, // and     arg arg
  XOR     = 10, // xor     arg arg

  SHR     = 11, // shr     arg arg
  SHL     = 12, // shl     arg arg
  ROR     = 13, // ror     arg arg
  ROL     = 14, // rol     arg arg

  INC     = 15, // inc     arg
  DEC     = 16, // dec     arg

  MOV     = 17, // mov     arg arg

  CMP     = 18, // cmp     arg arg
  TEST    = 19, // test    arg arg

  JMP     = 20, // jmp     arg        --
  JO      = 21, // jo      arg          |
  JNO     = 22, // jno     arg          |
  JS      = 23, // js      arg          |
  JNS     = 24, // jns     arg          |
  JE      = 25, // je      arg          | sign agnostic jumps
  JZ      = 25, // jz      arg          |
  JNE     = 26, // jne     arg          |
  JNZ     = 26, // jnz     arg          |
  JP      = 27, // jp      arg          |
  JPE     = 27, // jpe     arg          |
  JNP     = 28, // jnp     arg          |
  JPO     = 28, // jpo     arg        --

  JL      = 29, // jl      arg        --
  JNGE    = 29, // jnge    arg          |
  JGE     = 30, // jge     arg          |
  JNL     = 30, // jnl     arg          | unsigned jumps
  JLE     = 31, // jle     arg          |
  JNG     = 31, // jng     arg          |
  JG      = 32, // jg      arg          |
  JNLE    = 32, // jnle    arg        --

  JB      = 33, // jb      arg        --
  JNAE    = 33, // jnae    arg          |
  JC      = 33, // jc      arg          |
  JAE     = 34, // jae     arg          |
  JNB     = 34, // jnb     arg          | signed jumps
  JNC     = 34, // jnc     arg          |
  JBE     = 35, // jbe     arg          |
  JNA     = 35, // jna     arg          |
  JA      = 36, // ja      arg          |
  JNBE    = 36, // jnbe    arg        --

  PUSH    = 37, // push    arg
  POP     = 38, // pop     arg
  FPUSH   = 39, // fpush   arg        -- flag
  FPOP    = 40, // fpush   arg
  APUSH   = 41, // apush   arg        -- all
  APOP    = 42, // apush   arg

  CALL    = 43, // call    arg
  RET     = 44, // ret

  SYSCALL = 45, // syscall arg
                // valid syscalls are
                //   0  read
                //   1  write
                // 255  exit

  HLT     = 46, // hlt
};
