/*
 * paging.h
 *
 *  Created on: 05/lug/2010
 *      Author: RaimondoS
 */

#include "../types.h"
#include "isr.h"

#ifndef PAGING_H_
#define PAGING_H_

/*!
 * \struct page_t
 * \brief Structure describing a page
 */
struct page_t
{
    uint32_t present    : 1;    /*!< Page present in memory. */
    uint32_t rw         : 1;    /*!< Read-only if clear, read-write if set */
    uint32_t user       : 1;    /*!< Supervisor level only if clear */
    uint32_t accessed   : 1;    /*!< Has the page been accessed since last refresh ? */
    uint32_t dirty      : 1;    /*!< Has the page been written to since last refresh ? */
    uint32_t unused     : 7;    /*!< Amalgation of unused and reserved bits */
    uint32_t frame      : 20;   /*!< Frame address (shifted right 12 bits) */
};

/*!
 * \struct page_table_t
 * \brief Structure describing a table of page
 */
struct page_table_t
{
    struct page_t pages[1024];
};

/*!
 * \struct page_directory_t
 * \brief Structure describing a page directory
 */
struct page_directory_t
{
    struct page_table_t *tables[1024];  /*!< Array of pointers to pagetables */
    size_t physical_tables[1024];     /*!< Array of pointers to pagetables above, but gives their *physical* location, for loading into the CR3 register. */
    size_t physical_addr;             /*!< The physical address of physical_tables. This comes into play when we get our kernel heap allocated and the directory may be different location in virtual memory. */
};

void alloc_frame (struct page_t *page, int is_kernel, int is_writeable);
void free_frame (struct page_t *page);

void init_paging (void);
void switch_page_directory (struct page_directory_t *dir);
struct page_t *get_page (size_t address, bool make, struct page_directory_t *dir);
void page_fault (struct registers_t *regs);
struct page_directory_t *clone_directory (struct page_directory_t *src);

#endif /* PAGING_H_ */
