#!/usr/bin/env python
# simple client, sends messages to server

import socket

port = 1234

# create an INET, STREAMing socket
clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# now connect to the web server on port 80 - the normal http port
clientsocket.connect(("localhost", port))

clientsocket.send("aaaaa")

print clientsocket.recv(1024)

# Close the socket when done
clientsocket.close()                     
