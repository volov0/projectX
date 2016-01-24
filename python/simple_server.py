#!/usr/bin/env python
# simple server, listens on port and prints incoming messages

import socket
from thread import *

port = 1234
#addr = "localhost"
addr = "10.0.2.15"

def clientthread(c):
	print c.recv(1024)                  # Recieve data from client
	c.send('Thank you for connecting')  # Reply to client
	c.close()                # Close the connection
	
# create an INET, STREAMing socket
serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# bind the socket to a public host, and a well-known port
#serversocket.bind((socket.gethostname(), port))
serversocket.bind((addr, port))

print socket.gethostbyname(socket.gethostname())

# become a server socket
serversocket.listen(5)
while True:
	c, addr = serversocket.accept()     # Establish connection with client.
	print 'Got connection from', addr
	#start new thread takes 1st argument as a function name to be run, second is the tuple of arguments to the function.
	start_new_thread(clientthread ,(c,))


