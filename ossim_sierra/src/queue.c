#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
        if (q == NULL) return 1;
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
        /* TODO: put a new process to queue [q] */
	if (q != NULL && proc  != NULL && q->size < MAX_QUEUE_SIZE){
		q->proc[q->size] = proc;
		q->size++;
	}


}

struct pcb_t * dequeue(struct queue_t * q) {
        /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */
	struct pcb_t *proc = NULL;
	if (q == NULL || empty(q))
		return proc;

	int min_priority = 0;
	for (int i = 1; i < q->size; i++) {
		if (q->proc[i]->priority < q->proc[min_priority]->priority) {
			min_priority = i;
		}
	}
	
	proc = q->proc[min_priority];
	for (int i = min_priority; i < q->size - 1; i++) {
		q->proc[i] = q->proc[i + 1];
	}
	q->size--;
	q->proc[q->size] = NULL;
	return proc;
}

