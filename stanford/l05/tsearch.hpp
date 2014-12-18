/**
 * @file   tsearch.hpp
 * @author volovo
 * @date   18.12.2014  
 * @brief  Template search 
 * @detail Genericke vyhledavani v poli libovolnych struktur.
 */

#ifndef TSEARCH_HPP
#define TSEARCH_HPP

#include <vector>

/**
 * Template function tsearch
 * -------------------------
 * @param1 key - klic toho co se hleda v poli
 * @param2 v - vecor/pole kde se hleda
 * @return pozice klice key v poli nebo -1 kdyz nenalezeno 
 */
template <class T>
int tsearch(T key, std::vector<T>& v);

#endif  /* TSEARCH_HPP */
