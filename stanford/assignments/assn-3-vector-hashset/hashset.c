#include "hashset.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void HashSetNew(hashset *h, int elemSize, int numBuckets,
		HashSetHashFunction hashfn, HashSetCompareFunction comparefn, HashSetFreeFunction freefn) {
	assert(elemSize > 0);
	assert(numBuckets > 0);
	assert(hashfn != NULL);
	assert(comparefn != NULL);

	h->elem_size = elemSize;
	h->num_buckets = numBuckets;
	h->hashfn = hashfn;
	h->comparefn = comparefn;
	h->freefn = freefn;

	h->base = malloc(h->num_buckets * sizeof(vector));
 	assert(h->base != NULL);

	vector *tvect;
	for (int i = 0; i < h->num_buckets; i++) {
		tvect = (vector *)NthElemAddr(h->base, sizeof(vector), i);
		VectorNew(tvect, h->elem_size, h->freefn, 4);
	}
}

void HashSetDispose(hashset *h) {
	int i;
	for (i = 0; i < h->num_buckets; i++) 
		VectorDispose((vector *)NthElemAddr(h->base, sizeof(vector), i));
	
	h->num_buckets = 0;
	free(h->base);
}

int HashSetCount(const hashset *h) { 
	int i, sum = 0;
	for (i = 0; i < h->num_buckets; i++) 
		sum += VectorLength((vector *)NthElemAddr(h->base, sizeof(vector), i));
	return sum;
}

void HashSetMap(hashset *h, HashSetMapFunction mapfn, void *auxData) {
	assert(mapfn != NULL);
	for (int i = 0; i < h->num_buckets; i++) { 
		vector *tvect = (vector *)NthElemAddr(h->base, sizeof(vector), i);
		VectorMap(tvect, mapfn, auxData);
	}
}

void HashSetEnter(hashset *h, const void *elemAddr) {
	/* check if matching element is already in hashset */
	void *eptr = HashSetLookup(h, elemAddr);
	if (eptr != NULL)                         // element found - just overwrite old one 
		memcpy(eptr, elemAddr, h->elem_size);
	else {                                    // element not found - append to vector
		int position = h->hashfn(elemAddr, h->num_buckets);
		vector *tvect = (vector *)NthElemAddr(h->base, sizeof(vector), position);
		VectorAppend(tvect, elemAddr);
	}
}

void *HashSetLookup(const hashset *h, const void *elemAddr) {
	assert(elemAddr != NULL);
	int position = h->hashfn(elemAddr, h->num_buckets);
	assert(ValidPosition(position, h->num_buckets));
	
	/* try to find element in vector */
	vector *tvect = (vector *)NthElemAddr(h->base, sizeof(vector), position);
	position = VectorSearch(tvect, elemAddr, h->comparefn, 0, false);
	if (position >= 0)
		return VectorNth(tvect, position);
	else
		return NULL;
}
