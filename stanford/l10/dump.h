/**
 * @file dump.h
 * @author volovo
 * @date 19.12.2014
 * @brief Hexadecimal memory dump
 */

#ifndef DUMP_H
#define DUMP_H

#if UINTPTR_MAX == 0xffffffff
/* 32-bit */
#elif UINTPTR_MAX == 0xffffffffffffffff
/* 64-bit */
#else
/* wtf */
#endif

/**
 * Function dump
 * -------------
 * @param1 addr
 * @param2 len
 *
 * @brief vydampuje pamet na adrese addr o delce len.
 */
void dump(void *addr, int len);

/**
 * Function dump_stack
 * -------------------
 * @param1 depth kolik stacku do hloubky se ma vydumpovat
 * @brief dumpuje obsah stacku 
 */
void dump_stack(int depth);

/**
 * Function dump_code
 * ------------------
 * @param1 length delka machine kodu, ktery se dumpuje
 * @brief vydumpuje hexadecimalne strojovy kod od aktualni instrukce
 */
void dump_code(int length);


#endif  /* DUMP_H */
