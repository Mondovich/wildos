/*
 * array.h
 *
 *  Created on: 05/lug/2010
 *      Author: RaimondoS
 */

#include "../types.h"

#ifndef ARRAY_H_
#define ARRAY_H_

typedef void* type_t;

typedef int8_t (*lessthan_predicate_t)(type_t,type_t);
/*!
 * \struct ordered_array_t
 * \brief Describe an ordered array
 */
typedef struct
{
    type_t *array;
    uint32_t size;
    uint32_t max_size;
    lessthan_predicate_t less_than;
} ordered_array_t;

int8_t standard_lessthan_predicate (type_t a, type_t b);

ordered_array_t create_ordered_array (uint32_t max_size, lessthan_predicate_t less_than);
ordered_array_t place_ordered_array  (void *addr, uint32_t max_size, lessthan_predicate_t less_than);
void destroy_ordered_array (ordered_array_t *array);
void insert_ordered_array (type_t item, ordered_array_t *array);
type_t lookup_ordered_array (uint32_t i, ordered_array_t *array);
void remove_ordered_array (uint32_t i, ordered_array_t *array);

#endif /* ARRAY_H_ */
