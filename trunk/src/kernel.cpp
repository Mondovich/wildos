#include "asm/asm.h"
#include "boot/multiboot.h"
#include "hw/gdt.h"
#include "hw/kheap.h"
#include "hw/screen.h"
#include "hw/memory.h"
#include "hw/paging.h"
#include "hw/syscall.h"
#include "hw/task.h"
#include "hw/timer.h"
#include "utils/string.h"

size_t initial_esp; // New global variable.

// Initialisation routine - zeroes all the interrupt service routines,
// initialises the GDT and IDT.
void init_descriptor_tables() {
	// Initialise the global descriptor table.
	init_gdt();
	init_idt();
}

extern "C" void _kmain(struct multiboot_t *mboot_ptr, size_t initial_stack) {

	initial_esp = initial_stack;
	// Clearing screen
	clear();
	// Writing Bootloader info
	puts((char*) mboot_ptr->boot_loader_name);
	putchar('\n');
	puts("WildOS booting up...");

	//Initialise descriptor tables
	fputs("Initializing descriptor tables...");
	init_descriptor_tables();
	puts("[ok]");

	fputs("Initializing timer...");
	sti();
	init_timer(50);
	puts("[ok]");

	fputs("Initializing paging...");
	int32_t a = (int32_t) kmalloc(8);
	init_paging();
	puts("[ok]");

	// Start multitasking.
	fputs("Initializing multitasking...");
	init_tasking();
	puts("[ok]");

	fputs("Initializing syscalls...");
	initialise_syscalls();
	puts("[ok]");

	// Create a new process in a new address space which is a clone of this.
	int ret = fork();

	cli();

	printk("fork() returned %x, and getpid() returned %x\n", ret, getpid());
	puts("==============================================");

	printk("a = %x\n", a);
	int32_t b = (int32_t) kmalloc(8);
	printk("b = %X\n", b);
	int32_t c = (int32_t) kmalloc(8);
	printk("c = %x\n", c);
	kfree((void *) b);
	kfree((void *) c);
	int32_t d = (int32_t) kmalloc(16);
	printk("d = %x\n", d);

	sti();

	//	fputs("Switching to user mode...");
	//	switch_to_user_mode();
	//	puts("[ok]");

	//	syscall_fputs("Hello, user world!\n");

	return;

}
