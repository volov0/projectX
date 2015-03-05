#!/usr/bin/env python
#encoding: utf-8
# Simple skript na rsg - generovani textu podle gramatiky

from random import choice,seed
import sys

# idealni struktura na gramatiku je dictionary, coz je hashovaci tabulka
grammar = {'<start>' : [['This', '<object>', 'is', '<adjective>']],
           '<object>' : [['word'], ['piece'], ['matter'], ['food']],
		   '<adjective>' : [['dark'], ['contemplating'], ['incendiary']]}

def expand(symbol):
	"Expanduje symbol do textu."
	if symbol.startswith("<"):
		definition = grammar[symbol]
		expansion = choice(definition)
		# map udela to, ze pusti funkci expand na kazdou polozku z expansion,
		# expansion je totiz pole
		map(expand, expansion)   
	else:
		sys.stdout.write(symbol+" ")

# nejprve zrandomizuju...
seed() 
expand('<start>')
