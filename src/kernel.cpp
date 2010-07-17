#include "kernel.h"
#include "asm/asm.h"
#include "boot/multiboot.h"
#include "hw/gdt.h"
#include "hw/kheap.h"
#include "hw/screen.h"
#include "hw/syscall.h"
#include "hw/memory.h"
#include "hw/paging.h"
#include "hw/task.h"
#include "hw/timer.h"
#include "utils/string.h"
#include "types.h"
#include "fs/initrd.h"
#include "fs/fs.h"
#include "Prova.h"

extern Multiboot multiboot;
extern uint32_t placement_address;
size_t initial_esp; // New global variable.

extern "C" void _kmain(struct multiboot_t *mboot_ptr, size_t initial_stack) {
	initial_esp = initial_stack;

	// Clearing screen
	clear();
	// Writing Bootloader info
	puts((char*) mboot_ptr->boot_loader_name);
	putchar('\n');
	printk("Lower memory: %i Kb\nUpper memory %i Kb\n\n", mboot_ptr->mem_lower, mboot_ptr->mem_upper);

	puts("WildOS booting up...");
	putchar('\n');

	//Initialise descriptor tables
	fputs("Initializing descriptor tables...");
	init_descriptor_tables();
	puts("[ok]");

	fputs("Initializing timer...");
	init_timer(50);
	puts("[ok]");

	enableInt();

	// Find the location of our initial ramdisk.
	if (mboot_ptr->mods_count > 0) {
		fputs("Loading RamDisk module...");
		uint32_t initrd_end = *(uint32_t*) (mboot_ptr->mods_addr + 4);
		// Don't trample our module with placement accesses, please!
		placement_address = initrd_end;
		puts("[ok]");
	}

	fputs("Initializing paging...");
	init_paging(mboot_ptr->mem_upper * 1024);
	puts("[ok]");

	// Start multitasking.
	fputs("Initializing multitasking...");
	init_tasking();
	puts("[ok]");

	fputs("Initializing syscalls...");
	initialise_syscalls();
	puts("[ok]");

	// Initialise the initial ramdisk, and set it as the filesystem root.
	if (mboot_ptr->mods_count > 0) {
		fputs("Initializing RamDisk...");
		uint32_t initrd_location = *((uint32_t*) mboot_ptr->mods_addr);
		fs_root = initialise_initrd(initrd_location);
		puts("[ok]");
	}

	// Create a new process in a new address space which is a clone of this.
	int ret = 0;//fork();

	printk("PID %i: ret = %i\n", getpid(), ret);
	if (ret == 0) {
		uint32_t a = (uint32_t) kmalloc(sizeof(uint32_t));
		printk("PID %i: a is at %x\n", getpid(), a);
	} else {
		uint32_t *b = (uint32_t*) kmalloc(sizeof(uint32_t));
		*b = 12;
		printk("PID %i: b = %i at %x\n", getpid(), *b, b);
	}

	// list the contents of /
	if (fs_root) {
		// The next section of code is not reentrant so make sure we aren't interrupted during.
		disableInt();
		int i = 0;
		dirent_t *node = 0;
		puts("\nReading contents of RamDisk");
		while ((node = readdir_fs(fs_root, i)) != 0) {
			printk("Found file %s\n", node->name);
			fs_node_t *fsnode = finddir_fs(fs_root, node->name);

			if ((fsnode->flags & 0x7) == FS_DIRECTORY) {
				fputs("(directory)\n");
			} else {
				fputs(" contents: \"");
				char buf[256];
				uint32_t sz = read_fs(fsnode, 0, 256, (uint8_t*) buf);
				int j;
				for (j = 0; j < sz; j++)
					putchar(buf[j]);

				fputs("\"\n");
			}
			i++;
		}
		fputs("\nEND\n");
		enableInt();
	}

	Prova *p = new Prova();
	p->setI(10);
	puts(p->getI());

	//	switch_to_user_mode();
	//
	//	syscall_fputs("Hello User World\n");

	return;

}

Kernel::Kernel()
{

}
Kernel::~Kernel() {

}

void Kernel::run() {
	// Clearing screen
	clear();
	// Writing Bootloader info
	puts((char*) multiboot.getBoot_loader_name());
	putchar('\n');
	printk("Lower memory: %i Kb\nUpper memory %i Kb\n\n", multiboot.getMem_lower(),
			multiboot.getMem_upper());

	puts("WildOS booting up...");
	putchar('\n');

}
