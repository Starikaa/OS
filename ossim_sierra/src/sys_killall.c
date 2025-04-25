/*
 * Copyright (C) 2025 pdnguyen of HCMC University of Technology VNU-HCM
 */

/* Sierra release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 */

#include "common.h"
#include "syscall.h"
#include "stdio.h"
#include "libmem.h"
#include "queue.h"
#include "string.h"
int __sys_killall(struct pcb_t *caller, struct sc_regs* regs)
{
    char proc_name[100];
    uint32_t data;

    //hardcode for demo only
    uint32_t memrg = regs->a1;
    
    /* TODO: Get name of the target proc */
    //proc_name = libread..
    int i = 0;
    data = 0;
    while (1) {
        libread(caller, memrg, i, &data);
        if (data == (uint32_t)-1) {
            proc_name[i] = '\0'; 
            break;
        }
        proc_name[i] = (char)data;
        i++;
    }
    printf("The procname retrieved from memregionid %d is \"%s\"\n", memrg, proc_name);

    /* TODO: Traverse proclist to terminate the proc
     *       stcmp to check the process match proc_name
     */
    //caller->running_list
    //caller->mlq_ready_queu
    struct pcb_t* proc;
    struct queue_t* queues[] = { (caller->running_list), caller->mlq_ready_queue };
    int num_queues = sizeof(queues) / sizeof(queues[0]);

    for (int q = 0; q < num_queues; q++) {
        struct queue_t* queue = queues[q];
        for (int idx = 0; idx < queue->size; idx++) {
            proc = dequeue(queue); 
            if (strcmp(proc->path, proc_name) == 0) {
                printf("Terminating process %s\n", proc->path);
                continue; 
            }
            enqueue(queue, proc); 
        }
    }

    /* TODO Maching and terminating 
     *       all processes with given
     *        name in var proc_name
     */

    return 0; 
}
