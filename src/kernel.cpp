#include "boot/multiboot.h"
#include "hw/gdt.h"
#include "hw/screen.h"
#include "hw/memory.h"
#include "utils/string.h"


// Initialisation routine - zeroes all the interrupt service routines,
// initialises the GDT and IDT.
void init_descriptor_tables()
{
   // Initialise the global descriptor table.
   init_gdt();
}

extern "C" void _kmain(struct multiboot_t *mboot_ptr, uint32_t initial_stack) {

	// Clearing screen
	clear();
	// Writing Bootloader info
	puts((char*) mboot_ptr->boot_loader_name);
	putchar('\n');
	//Initialise descriptor tables
	init_descriptor_tables();

	return;

}
