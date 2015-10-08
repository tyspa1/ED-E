#!/usr/bin/python
#Communication with esp8266 WiFi Actuators
#copyright (c) 2015 Tyler Spadgenske

import socket
import mraa
import json
import sys

def transmit(name, value):
    HOST = ''   # Symbolic name meaning all available interfaces
    PORT = 888 # Arbitrary non-privileged port

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print 'Socket created'

    try:
        s.bind((HOST, PORT))
    except socket.error , msg:
        print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
        sys.exit()

        print 'Socket bind complete'

    s.listen(10)
    print 'Socket now listening'

    #now keep talking with the client
    while 1:
        #wait to accept a connection - blocking call
        conn, addr = s.accept()
        print 'Connected with ' + addr[0] + ':' + str(addr[1])

        data = conn.recv(1024)
        reply = 'OK...' + data
        if not data:
            break

        conn.sendall(name)
        conn.sendall(value)

    conn.close()
    s.close()
    print 'closed.'

UDP_IP = "127.0.0.1"
UDP_PORT = 41235

# Sensor and parameter names to listen for
componentName = "lamp"
sensorName = "LED"

# Bind to UDP port 41235
sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

print "Listening on port", UDP_PORT

while True:
    data,addr = sock.recvfrom(4096)
    print "Received ", data, "from", addr[0]
    if addr[0] != "127.0.0.1":
        print "Rejecting external UDP message from", addr[0]
        continue
    js = json.loads(data)
    component = js["component"]
    command = js["command"]
    argvArray = js["argv"]
    if component == componentName:
        for argv in argvArray:
            name = argv['name']
            value = argv['value']
            print "name: " + name
            print "value: " + value
            if (name == sensorName):
                print "Oh yeah"
                transmit(name, value)
