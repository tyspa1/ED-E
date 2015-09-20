#Communication with ESP8266 Units
#copyright (c) 2015 Tyler Spadgenske

import socket
import select
import os

VERSION = '0.1.0'

class Server():
    def __init__(self):
        # List to keep track of socket descriptors
        self.CONNECTION_LIST = []
        self.RECV_BUFFER = 4096 # Advisable to keep it as an exponent of 2
        self.PORT = 21

        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # this has no effect, why ?
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_socket.bind(("0.0.0.0", self.PORT))
        self.server_socket.listen(10)

        # Add server socket to the list of readable connections
        self.CONNECTION_LIST.append(self.server_socket)

        self.device_data = ''

    def save_data(self):
        if self.device_data != '':
            device_type = self.device_data[0]
            device_id = self.device_data[1]
            device_input = self.device_data[2]
            print 'Saving to database...'
            print device_type
            print device_id
            print device_input
            if device_type == 'd':
                os.system("iotkit-admin observation FrontDoor 1")

    def run(self):
        print "Chat server started on PORT " + str(self.PORT)
        while True:
            # Get the list sockets which are ready to be read through select
            read_sockets,write_sockets,error_sockets = select.select(self.CONNECTION_LIST,[],[])

            for sock in read_sockets:
                #New connection
                if sock == self.server_socket:
                    # Handle the case in which there is a new connection recieved through self.server_socket
                    sockfd, addr = self.server_socket.accept()
                    self.CONNECTION_LIST.append(sockfd)
                    print "Client %s connected" % addr[0]

                #Some incoming message from a client
                else:
                    # Data recieved from client, process it
                    try:
                        #In Windows, sometimes when a TCP program closes abruptly,
                        # a "Connection reset by peer" exception will be thrown
                        data = sock.recv(self.RECV_BUFFER)
                        if data:
                            print str(sock.getpeername()[0]) + '>' + data  + ' recv'
                            self.device_data = data
                        else:
                            self.device_data = ''

                    except:
                        print "Client (%s, %s) is offline" % addr
                        sock.close()
                        self.CONNECTION_LIST.remove(sock)
                        continue
                        
        self.server_socket.close()

if __name__ == "__main__":
    serv = Server()
    try:
        serv.run()

    except KeyboardInterrupt:
        print 'Closing server...'
        serv.server_socket.close()
