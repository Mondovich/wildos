/*
 * multiboot.h -- Declares the multiboot info structure
 *
 *  Created on: 29/giu/2010
 *      Author: RaimondoS
 */

#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include "../types.h"

#define MULTIBOOT_FLAG_MEM     0x001
#define MULTIBOOT_FLAG_DEVICE  0x002
#define MULTIBOOT_FLAG_CMDLINE 0x004
#define MULTIBOOT_FLAG_MODS    0x008
#define MULTIBOOT_FLAG_AOUT    0x010
#define MULTIBOOT_FLAG_ELF     0x020
#define MULTIBOOT_FLAG_MMAP    0x040
#define MULTIBOOT_FLAG_CONFIG  0x080
#define MULTIBOOT_FLAG_LOADER  0x100
#define MULTIBOOT_FLAG_APM     0x200
#define MULTIBOOT_FLAG_VBE     0x400

struct {
	uint32_t num;
	uint32_t size;
	uint32_t addr;
	uint32_t shndx;
} elf_sec;

struct {
	uint32_t control_info;
	uint32_t mode_info;
	uint32_t mode;
	uint32_t interface_seg;
	uint32_t interface_off;
	uint32_t interface_len;

} vbe;
struct multiboot_t {
	uint32_t flags;
	uint32_t mem_lower;
	uint32_t mem_upper;
	uint32_t boot_device;
	uint32_t cmdline;
	uint32_t mods_count;
	uint32_t mods_addr;

	struct elf_sec;

	uint32_t mmap_length;
	uint32_t mmap_addr;
	uint32_t drives_length;
	uint32_t drives_addr;
	uint32_t config_table;
	uint32_t boot_loader_name;
	uint32_t apm_table;

	struct vbe;
}__attribute__((packed));

typedef struct multiboot_header multiboot_header_t;

class Multiboot {
	struct multiboot_t *mboot_ptr;
public:
	Multiboot();
	Multiboot(struct multiboot_t *);
	virtual ~Multiboot();

	uint32_t getAddr() const {
		return mboot_ptr->elf_sec->addr;
	}

	uint32_t getApm_table() const {
		return mboot_ptr->apm_table;
	}

	uint32_t getBoot_device() const {
		return mboot_ptr->boot_device;
	}

	uint32_t getBoot_loader_name() const {
		return mboot_ptr->boot_loader_name;
	}

	uint32_t getCmdline() const {
		return mboot_ptr->cmdline;
	}

	uint32_t getConfig_table() const {
		return mboot_ptr->config_table;
	}

	uint32_t getControl_info() const {
		return mboot_ptr->vbe->control_info;
	}

	uint32_t getDrives_addr() const {
		return mboot_ptr->drives_addr;
	}

	uint32_t getDrives_length() const {
		return mboot_ptr->drives_length;
	}

	uint32_t getFlags() const {
		return mboot_ptr->flags;
	}

	uint32_t getInterface_len() const {
		return mboot_ptr->interface_len;
	}

	uint32_t getInterface_off() const {
		return mboot_ptr->interface_off;
	}

	uint32_t getInterface_seg() const {
		return mboot_ptr->interface_seg;
	}

	uint32_t getMem_lower() const {
		return mboot_ptr->mem_lower;
	}

	uint32_t getMem_upper() const {
		return mboot_ptr->mem_upper;
	}

	uint32_t getMmap_addr() const {
		return mboot_ptr->mmap_addr;
	}

	uint32_t getMmap_length() const {
		return mboot_ptr->mmap_length;
	}

	uint32_t getMode() const {
		return mboot_ptr->mode;
	}

	uint32_t getMode_info() const {
		return mboot_ptr->mode_info;
	}

	uint32_t getMods_addr() const {
		return mboot_ptr->mods_addr;
	}

	uint32_t getMods_count() const {
		return mboot_ptr->mods_count;
	}

	uint32_t getNum() const {
		return mboot_ptr->num;
	}

	uint32_t getShndx() const {
		return mboot_ptr->shndx;
	}

	uint32_t getSize() const {
		return mboot_ptr->size;
	}
};

#endif
