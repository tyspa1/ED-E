#ED-E
#Ultimate Home Automation and Monitoring System
#copyright (c) 2015 Tyler Spadgenske
VERSION = "0.1.0"
import os
import time
from subprocess import Popen

class EDE():
    def __init__(self):
        pass

    def run(self):
        #Start base unit (C++)
        print "EDE Version " + VERSION
        print "***********************"
        print "Starting MySQL Server..."
        Popen(['mysqld'])
        time.sleep(2)
        print "Starting Monitoring Unit..."
        time.sleep(1)
        Popen(["/home/root/ED-E/base/src/./ED-E"])
        print "Starting Sensor Server..."
        print "Failed! (NOT IMPLEMENTED)"

if __name__ == "__main__":
    s = EDE()
    s.run()