/*
 * gdt.h
 *
 *  Created on: 02/lug/2010
 *      Author: RaimondoS
 */

#ifndef GDT_H_
#define GDT_H_

/*!
 * \struct gdt_entry_t
 * \brief Structure describing a segment's descriptor.
 */
struct gdt_entry_t
{
    uint16_t limit_low;     /*!< The lower 16 bits of the limit. */
    uint16_t base_low;      /*!< The lower 16 bits of the base. */
    uint8_t  base_middle;   /*!< The next 8 bits of the base. */
    uint8_t  access;        /*!< Access flags, determine what ring this segment can be used in. */
    uint8_t  granularity;
    uint8_t  base_high;     /*!< The last 8 bits of the base. */
} __attribute__ ((packed));

/*!
 * \struct gdt_t
 * \brief Address of the GDT (base/limit).
 */
struct gdt_t
{
    uint16_t limit; /*!< The upper 16 bits of all selector limits. */
    uint32_t base;  /*!< The address of the first gdt_entry_t struct. */
} __attribute__ ((packed));

#endif /* GDT_H_ */
