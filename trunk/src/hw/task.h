/*
 * task.h
 *
 *  Created on: 07/lug/2010
 *      Author: RaimondoS
 */

#ifndef TASK_H_
#define TASK_H_

#include "../types.h"
#include "paging.h"

#define KERNEL_STACK_SIZE 2048       // Use a 2kb kernel stack.
// This structure defines a 'task' - a process.
typedef struct task {
	int id; // Process ID.
	size_t esp, ebp; // Stack and base pointers.
	size_t eip; // Instruction pointer.
	struct page_directory_t *page_directory; // Page directory.
	size_t kernel_stack; // Kernel stack location.
	struct task *next; // The next task in a linked list.
} task_t;

// Initialises the tasking system.
void initialise_tasking();

// Called by the timer hook, this changes the running process.
void switch_task();

void switch_to_user_mode();

// Forks the current process, spawning a new one with a different
// memory space.
int fork();

// Causes the current process' stack to be forcibly moved to a new location.
void move_stack(void *new_stack_start, size_t size);

// Returns the pid of the current process.
int getpid();

#endif /* TASK_H_ */
