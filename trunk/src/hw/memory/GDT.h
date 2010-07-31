/*
 * GDT.h
 *
 *  Created on: 28/lug/2010
 *      Author: RaimondoS
 */


#ifndef GDT_H_
#define GDT_H

#include "../../common/types.h"
#include "TSS.h"
#include "../../log/Log.h"
#include "../../utils/string.h"

namespace Hardware {

/*!
 * \struct gdt_entry_t
 * \brief Structure describing a segment's descriptor.
 */
struct gdt_entry_t {
	uint16_t limitLow; /*!< The lower 16 bits of the limit. */
	uint16_t baseLow; /*!< The lower 16 bits of the base. */
	uint8_t baseMiddle; /*!< The next 8 bits of the base. */
	uint8_t access; /*!< Access flags, determine what ring this segment can be used in. */
	uint8_t granularity;
	uint8_t baseHigh; /*!< The last 8 bits of the base. */
}__attribute__ ((packed));

/*!
 * \struct gdt_t
 * \brief Address of the GDT (base/limit).
 */
struct gdt_t {
	uint16_t limit; /*!< The upper 16 bits of all selector limits. */
	uint32_t base; /*!< The address of the first gdt_entry_t struct. */
}__attribute__ ((packed));

extern "C" void gdtFlush(uint32_t addr);

class GDT {
	gdt_entry_t entries[6];
	gdt_t addr;
//	tss_entry_t tssEntry;
	TSS tss;
public:
	GDT() {};
	virtual ~GDT() {};
	void init();
	void writeTss(int32_t num, uint16_t ss0, uint32_t esp0);
	void setGate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
private:

};

} // namespace Hardware


#endif /* GDT_H_ */
