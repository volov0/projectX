#!/usr/bin/env python
# Ukazka na networking a xml

from urllib2 import urlopen
from xml.sax import make_parser, ContentHandler
import sys


class RSSHandler(ContentHandler):
	"""RSSHandler je odvozena od tridy ContentHandler, ktera sama o sobe nic nedela.
	Cilem je parsovat xml, ktere je RSS"""

	def __init__(self):
		ContentHandler.__init__(self)  # buhvi co to dela, ale treba je to neco duleziteho
		self.__inItem  = False         # promenna pro processing, __ znamena, ze je privatni, je to spi konvence
		self.__inTitle = False         # dtto, privatnost v pythonu uplne nefunguje, je to slozitejsi
	
	def startElement(self, tag, attrs):
		if tag == "item":
			self.__inItem = True
		if (tag == "title") & self.__inItem:  # zajima me pouze title, ktery je uvnitr item
			self.__inTitle = True
	
	def endElement(self, tag):
		if tag == "item":
			self.__inItem = False
		if (tag == "title") & self.__inItem:
			sys.stdout.write("\n")
			self.__inTitle = False

	def characters(self, data):
		if self.__inTitle:
			sys.stdout.write(data)
	

def listFeedTitles(url):
	sys.stdout.write(url + "\n")
	infile = urlopen(url)                   # kaslu na error checking
	parser = make_parser()                  # vraci nejaky genericky xml parser
	parser.setContentHandler(RSSHandler())  # rikam co ma parser delat
	parser.parse(infile)                    # neco delej v zavisloxti na content handleru

listFeedTitles('http://feeds.feedburner.com/uk/gizmodo')

# ContentHandler vypada zhruba takhle:
#
# class ContentHandler   # pass znamena, ze metody jsou pouze prototypy
#
#    def startElement(self, tag, attrs): pass    # atributy dostane ve forme dictionary
#
#    def endElement(self, tag): pass
#
#    def characters(self, data): pass
#
# pak jsou tu jeste dalsi, ktere me ted nezajimaji (default konstrukor, startDocument, endDocument, ...)
#

