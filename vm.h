#include <stdint.h>

struct vm {
  // 16-bit wide pointers
  uint8_t memory[1<<16];

  // 16 16-bit wide general purpose registers
  uint16_t regs[16];
  // instruction pointer
  uint16_t rip;

  union {
    uint8_t flags;
    struct {
      uint8_t cf:1,
              pf:1,
              zf:1,
              sf:1,
              df:1,
              of:1;
    };
  };
};
