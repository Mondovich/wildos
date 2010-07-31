/*
 * heap.h
 *
 *  Created on: 05/lug/2010
 *      Author: RaimondoS
 */

#ifndef HEAP_H_
#define HEAP_H_

#include "../common/types.h"
#include "../utils/array.h"

#define KHEAP_START         0xC0000000
#define KHEAP_INITIAL_SIZE  0x100000

#define HEAP_INDEX_SIZE   	0x20000
#define HEAP_MAGIC        	0x123890AB
#define HEAP_MIN_SIZE     	0x70000

#define ISALIGNED(ADDR)		((ADDR) & 0x00000FFF == 0)

/*! \struct header_t */
typedef struct
{
    uint32_t magic;     /*!< Magic number, used for error checking and identification. */
    uint8_t is_hole;    /*!< 1 if this is a hole. 0 if this is a block. */
    uint32_t size;      /*!< Size of the block, including the end footer. */
} header_t;

/*! \struct footer_t */
typedef struct
{
    uint32_t magic;             /*!< Magic number, same as in header_t */
    header_t *header;    /*!< Pointer to the block header */
} footer_t;

/*! \struct heap_t */
typedef struct
{
    ordered_array_t index;
    size_t start_address; /*!< The start of our allocated space. */
    size_t end_address;   /*!< The end of our allocated space. May be expanded up to max_address. */
    size_t max_address;   /*!< The maximum address the heap can be expanded to */
    uint8_t supervisor;     /*!< Should extra pages requested by us mapped as supervisor-only ? */
    uint8_t readonly;       /*!< Should extra pages requested by us mapped as read-only ? */
} heap_t;

heap_t *create_heap (size_t start, size_t end_addr, size_t max, uint8_t supervisor, uint8_t readonly);
void *alloc (size_t size, bool page_align, heap_t *heap);
void free (void *p, heap_t *heap);

void *kmalloc (size_t size, bool align, size_t *phys);
void *kmalloc (size_t size, bool align);
void *kmalloc (size_t size, size_t *phys);
void *kmalloc (size_t size);
void kfree (void *p);

#endif /* HEAP_H_ */
