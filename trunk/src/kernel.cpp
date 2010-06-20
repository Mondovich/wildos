#include "kernel.h"

extern "C" void _kmain(void* mbd, unsigned int magic) {
	if (magic != 0x2BADB002) {
		/* Something went not according to specs. Print an error */
		/* message and halt, but do *not* rely on the multiboot */
		/* data structure. */
	}

	/* You could either use multiboot.h */
	/* (http://www.gnu.org/software/grub/manual/multiboot/multiboot.html#multiboot_002eh) */
	/* or do your offsets yourself. The following is merely an example. */
	char * boot_loader_name = (char*) ((long*) mbd)[16];
	//strcat(boot_loader_name, "\r\n");

	monitor_clear();
	strcat(boot_loader_name, "\r\n");
	monitor_write(boot_loader_name);

	/* Write your kernel here. */
	char hello[80];
	strcpy(hello, "Ciao Mondo!");
	strcat(hello, "\r\n");
	strcat(hello, "Sono il tuo OS!");
	monitor_write(hello);
}
