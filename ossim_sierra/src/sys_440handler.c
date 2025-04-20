#include ”common.h”
 #include ”syscall .h”
 #include ”stdio .h”
int sys_440handler(struct pcb t ∗caller , struct sc regs∗ reg)
 {
 /* TODO: implement syscall job */
 printf(”The first system call parameter%d\n”, regs−>a1);
 return 0;
 }
