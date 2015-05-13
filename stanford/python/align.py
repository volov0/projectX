#!/usr/bin/env python

import random # for seed, random
import sys    # for stdout
import copy   # for copy

# Computes the score of the optimal alignment of two DNA strands.
def findOptimalAlignment(strand1, strand2, acache):
	
	# if one of the two strands is empty, then there is only
	# one possible alignment, and of course it's optimal
	if len(strand1) == 0: return {'strand1' : strand1, 'strand2' : strand2, 'score' : len(strand2) * -2}
	if len(strand2) == 0: return {'strand1' : strand1, 'strand2' : strand2, 'score' : len(strand1) * -2}

	# check for match in cache
	if strand1 + '-' + strand2 in acache:
		return copy.copy(acache[strand1 + '-' + strand2])

	# There's the scenario where the two leading bases of
	# each strand are forced to align, regardless of whether or not
	# they actually match.
	bestWith = findOptimalAlignment(strand1[1:], strand2[1:], acache)
	if strand1[0] == strand2[0]: 
		best = {'strand1' : strand1[0] + bestWith['strand1'],             
                'strand2' : strand2[0] + bestWith['strand2'], 
				'score' : bestWith['score'] + 1}   # no benefit from making other recursive calls
		acache[strand1 + '-' + strand2] = copy.copy(best)
		return best

	best = bestWith
	best['strand1'] = strand1[0] + bestWith['strand1'] 
	best['strand2'] = strand2[0] + bestWith['strand2']
	best['score'] = bestWith['score'] - 1
	
	# It's possible that the leading base of strand1 best
	# matches not the leading base of strand2, but the one after it.
	bestWithout = findOptimalAlignment(strand1, strand2[1:], acache)
	bestWithout['score'] -= 2 # penalize for insertion of space
	if bestWithout['score'] > best['score']:
		best = bestWithout
		best['strand1'] = " " + bestWithout['strand1']
		best['strand2'] = strand2[0] + bestWithout['strand2']

	# opposite scenario
	bestWithout = findOptimalAlignment(strand1[1:], strand2, acache)
	bestWithout['score'] -= 2 # penalize for insertion of space	
	if bestWithout['score'] > best['score']:
		best = bestWithout
		best['strand1'] = strand1[0] + bestWithout['strand1']
		best['strand2'] = " " + bestWithout['strand2']

	acache[strand1 + '-' + strand2] = copy.copy(best)
	return best

# Utility function that generates a random DNA string of
# a random length drawn from the range [minlength, maxlength]
def generateRandomDNAStrand(minlength, maxlength):
	assert minlength > 0, \
	       "Minimum length passed to generateRandomDNAStrand" \
	       "must be a positive number" # these \'s allow mult-line statements
	assert maxlength >= minlength, \
	       "Maximum length passed to generateRandomDNAStrand must be at " \
	       "as large as the specified minimum length"
	strand = ""
	length = random.choice(xrange(minlength, maxlength + 1))
	bases = ['A', 'T', 'G', 'C']
	for i in xrange(0, length):
		strand += random.choice(bases)
	return strand

# Method that just prints out the supplied alignment score.
# This is more of a placeholder for what will ultimately
# print out not only the score but the alignment as well.

def printAlignment(alignment, out = sys.stdout):	
	good = []
	bad = []
	for i in range(max(len(alignment['strand1']), len(alignment['strand2']))):
		if i + 1 > min(len(alignment['strand1']), len(alignment['strand2'])):
			good.append(" ")
			bad.append("2")
		elif (alignment['strand1'][i] == " ") or (alignment['strand2'][i] == " "): 
			good.append(" ")
			bad.append("2")
		elif alignment['strand1'][i] == alignment['strand2'][i]:
			good.append("1")
			bad.append(" ")
		else:
			good.append(" ")
			bad.append("1")

	out.write("Optimal alignment score is " + str(alignment['score']) + "\n")
	out.write("   + " + "".join(good) + "\n")
	out.write("     " + alignment['strand1'] + "\n")
	out.write("     " + alignment['strand2'] + "\n")
	out.write("   - " + "".join(bad) + "\n")
	out.write("---------------------------------------------------------------------" + "\n")

# Unit test main in place to do little more than
# exercise the above algorithm.  As written, it
# generates two fairly short DNA strands and
# determines the optimal alignment score.
#
# As you change the implementation of findOptimalAlignment
# to use memoization, you should change the 8s to 40s and
# the 10s to 60s and still see everything execute very
# quickly.
 
def main():
	acache = {}
	while (True):
		sys.stdout.write("Generate random DNA strands? ")
		answer = sys.stdin.readline()
		if answer == "no\n": break
		#strand1 = "TCCATATATTGGACGATATACCAGATTCGCCACCTTGTCAGTGGTTGCCCGTAGGG"
		#strand2 = "TTTCCTGCCCAAGAGTTTCCGACTTGTCCAGGGGTTGCCCGCCGTTGCGGCGCGGG"
		#strand1 = "TGTCGAGAATATCTTTCCTGTGGCTCAGACGCAGCGGTCCCCGTAGTCAA"
		#strand2 = "AGCCGGGGTAATGCGCACGGGAGCCTGCATTTACAATAGCCAGGTGCCCATTTTCAAC"
		strand1 = generateRandomDNAStrand(74, 90)
		strand2 = generateRandomDNAStrand(74, 90)
		sys.stdout.write("Aligning these two strands: " + strand1 + "\n")
		sys.stdout.write("                            " + strand2 + "\n")
		alignment = findOptimalAlignment(strand1, strand2, acache)
		printAlignment(alignment)
		
if __name__ == "__main__":
  main()
