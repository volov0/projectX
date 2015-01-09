#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>
#include <assert.h>

void VectorNew(vector *v, int elemSize, VectorFreeFunction freeFn, int initialAllocation) {
	v->elem_size = elemSize;
	v->allocated_elems = initialAllocation;
	v->used_elems = 0;
	v->freeFn = freeFn;
	v->base = malloc(v->allocated_elems * v->elem_size);
	assert(v->base != NULL);
}

void VectorDispose(vector *v) {
	int i;
	if(v->freeFn != NULL) {
		for (i = 0; i < v->used_elems; i++) 
			v->freeFn(NthElemAddr(v->base, v->elem_size, i));
	}
	v->allocated_elems = 0;
	v->used_elems = 0;
	free(v->base);
}

int VectorLength(const vector *v) { 
	return v->used_elems; 
}

void *VectorNth(const vector *v, int position) { 
	assert(ValidPosition(position, v->used_elems)); 

	return NthElemAddr(v->base, v->elem_size, position);
}

void VectorReplace(vector *v, const void *elemAddr, int position) {
	assert(ValidPosition(position, v->used_elems)); 

	if (v->freeFn != NULL) v->freeFn(NthElemAddr(v->base, v->elem_size, position));
	memcpy(NthElemAddr(v->base, v->elem_size, position), elemAddr, v->elem_size);
}

static void VectorGrow(vector *v) {
	v->allocated_elems *= 2;
	v->base = realloc(v->base, v->allocated_elems * v->elem_size);
	assert(v->base != NULL);
}

void VectorInsert(vector *v, const void *elemAddr, int position) {
	assert(ValidPosition(position, v->used_elems + 1)); 

	if (v->used_elems == v->allocated_elems) 
		VectorGrow(v);
	
	/* shift elements if necessary */
	if (position < v->used_elems) {
		memmove(NthElemAddr(v->base, v->elem_size, position + 1), 
		        NthElemAddr(v->base, v->elem_size, position),
				v->used_elems - position);
	}

	memcpy(NthElemAddr(v->base, v->elem_size, position), elemAddr, v->elem_size);
}

void VectorAppend(vector *v, const void *elemAddr) {	
	if (v->used_elems == v->allocated_elems) 
		VectorGrow(v);
	
	memcpy(NthElemAddr(v->base, v->elem_size, v->used_elems), elemAddr, v->elem_size);
	v->used_elems++;

}

void VectorDelete(vector *v, int position) {
	assert(ValidPosition(position, v->used_elems)); 
}

void VectorSort(vector *v, VectorCompareFunction compare) {
	qsort(v->base, v->used_elems, v->elem_size, compare);
}

void VectorMap(vector *v, VectorMapFunction mapFn, void *auxData) {
	int i;
	for (i = 0; i < v->used_elems; i++)
		mapFn(NthElemAddr(v->base, v->elem_size, i), auxData);
}

static const int kNotFound = -1;
int VectorSearch(const vector *v, const void *key, VectorCompareFunction searchFn, int startIndex, bool isSorted) { 
	char *res;

	if (isSorted) 
		res = bsearch(key, v->base, v->used_elems, v->elem_size, searchFn);
	else
		;//res = lsearch(key, v->base, &(v->used_elems), v->elem_size, searchFn);
	
	if (res == NULL) return kNotFound;

	return (res - (char *)v->base) / v->elem_size;
} 
