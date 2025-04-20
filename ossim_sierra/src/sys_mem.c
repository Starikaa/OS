/*
 * Copyright (C) 2025 pdnguyen of HCMC University of Technology VNU-HCM
 */

/* Sierra release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 */

#include "syscall.h"
#include "libmem.h"
#include "mm.h"

//typedef char BYTE;

int __sys_memmap(struct pcb_t *caller, struct sc_regs* regs)
{
   int memop = regs->a1;
   BYTE value;

   switch (memop) {
   case SYSMEM_MAP_OP:
            /* Reserved process case*/
       struct vm_rg_struct* new_region = malloc(sizeof(struct vm_rg_struct));
       if (get_free_vmrg_area(caller, regs->a2, regs->a3, new_region) == 0) {
           enlist_vm_freerg_list(caller->mm, new_region);
           printf("Memory region mapped: start=%d, end=%d\n", new_region->rg_start, new_region->rg_end);
       }
       else {
           printf("Failed to map memory region for process.\n");
       }
            break;
   case SYSMEM_INC_OP:
            inc_vma_limit(caller, regs->a2, regs->a3);
            break;
   case SYSMEM_SWP_OP:
            __mm_swap_page(caller, regs->a2, regs->a3);
            break;
   case SYSMEM_IO_READ:
            MEMPHY_read(caller->mram, regs->a2, &value);
            regs->a3 = value;
            break;
   case SYSMEM_IO_WRITE:
            MEMPHY_write(caller->mram, regs->a2, regs->a3);
            break;
   default:
            printf("Memop code: %d\n", memop);
            break;
   }
   
   return 0;
}


