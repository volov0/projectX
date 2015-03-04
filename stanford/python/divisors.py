# Function: gatherDivisors
# ------------------------
# Accepts the specified number and produces
# a list of all numbers that divide evenly
# into it.
# pustim to takhle:
# bash:python
# >>> import divisors              // tenhle command v podstate naloaduje divisors.py, je to podobne namaspacu v C++
# >>> divisors.gatherDivisors(24)  // zacne pocitat
# anebo:
# bash:python
# >>> from divisors import gatherDivisors
# >>> gatherDivisors(24)  

# whitespaces jou nutne nahrazuji kudrnate zavorky z C/C++

def gatherDivisors(number):
	"""Synthesizes a list of all the positive numbers 
	that evenly divide into the specified num."""        # prvni string ve funkci je comment; """ znamenam ze je na vic radek
	divisors = []
	for div in range(1, number + 1):    # range vyhodi vse od jedne az do number
		if number % div == 0:
			divisors.append(div)
	return divisors
