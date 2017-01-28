#ifndef MOLTAROS_PROCESS_H
#define MOLTAROS_PROCESS_H

#include <include/x86/idt.h>
#include <stddef.h>

typedef void (*task_fp)(void *);

typedef struct process {
	uint32_t *page_directory;
	uint32_t eip;
	uint32_t esp;
	uint32_t ebp;
	uint32_t stack_start;
	size_t id;
	struct process *next;
} proc_t;

void proc_init();

int fork();

#endif /* endif MOLTAROS_PROCESS_H */