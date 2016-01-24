#!/usr/bin/env python
# simple server, listens on port and prints incoming messages

import socket

port = 1234

# create an INET, STREAMing socket
serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# bind the socket to a public host, and a well-known port
#serversocket.bind((socket.gethostname(), port))
serversocket.bind(("localhost", port))

# become a server socket
serversocket.listen(5)
while True:
	c, addr = serversocket.accept()     # Establish connection with client.
	print 'Got connection from', addr
	print c.recv(1024)                  # Recieve data from client
	c.send('Thank you for connecting')  # Reply to client
	c.close()                # Close the connection
