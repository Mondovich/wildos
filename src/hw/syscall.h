/*
 * syscalls.h
 *
 *  Created on: 07/lug/2010
 *      Author: RaimondoS
 */

#ifndef SYSCALLS_H_
#define SYSCALLS_H_

#include "../common/stdarg.h"

void initialise_syscalls();

#define DECL_SYSCALL0(fn) int syscall_##fn();
#define DECL_SYSCALL1(fn,p1) int syscall_##fn(p1);
#define DECL_SYSCALL2(fn,p1,p2) int syscall_##fn(p1,p2);
#define DECL_SYSCALL3(fn,p1,p2,p3) int syscall_##fn(p1,p2,p3);
#define DECL_SYSCALL4(fn,p1,p2,p3,p4) int syscall_##fn(p1,p2,p3,p4);
#define DECL_SYSCALL5(fn,p1,p2,p3,p4,p5) int syscall_##fn(p1,p2,p3,p4,p5);
#define DECL_SYSCALL1N(fn,p1,...) int syscall_##fn(p1,...);

#define DEFN_SYSCALL0(fn, num) \
int syscall_##fn() \
{	\
	int a; \
	asm volatile("int $0x80" : "=a" (a) : "0" (num)); \
	return a; \
}

#define DEFN_SYSCALL1(fn, num, P1) \
int syscall_##fn(P1 p1) \
{	\
	int a; \
	asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1)); \
	return a; \
}

#define DEFN_SYSCALL2(fn, num, P1, P2) \
int syscall_##fn(P1 p1, P2 p2) \
{	\
	int a; \
	asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1), "c" ((int)p2)); \
	return a; \
}

#define DEFN_SYSCALL3(fn, num, P1, P2, P3) \
int syscall_##fn(P1 p1, P2 p2, P3 p3) \
{	\
	int a; \
	asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1), "c" ((int)p2)), "d" ((int)p3)); \
	return a; \
}

#define DEFN_SYSCALL4(fn, num, P1, P2, P3, P4) \
int syscall_##fn(P1 p1, P2 p2, P3 p3, P4 p4) \
{	\
	int a; \
	asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1), "c" ((int)p2)), "d" ((int)p3)), "S" ((int)p4)); \
	return a; \
}

#define DEFN_SYSCALL5(fn, num, P1, P2, P3, P4, P5) \
int syscall_##fn(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) \
{	\
	int a; \
	asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1), "c" ((int)p2), "d" ((int)p3)), "S" ((int)p4))), "D" ((int)p5)); \
	return a; \
}

#define DEFN_SYSCALL1N(fn, num, P1, ...) \
int syscall_##fn(P1 p1, ...) \
{	\
	int a; \
	asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" (p1)); \
	return a; \
}

DECL_SYSCALL1(fputs, const char*)
DECL_SYSCALL1N(printk, const char*, ...)

#endif /* SYSCALLS_H_ */
