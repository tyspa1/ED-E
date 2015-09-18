#ED-E Home Automation Installation Script
#copyright (c) 2015 Tyler Spadgenske
VERSION = "0.1.0"
import os
import time

class Install():
    def __init__(self):
        pass

    def install(self):
        self.logo()
        print "Installing sensors to cloud..."
        os.system("iotkit-admin register Air_Quality air.v1.0")
        os.system("iotkit-admin register MQ2_Gas gas.v1.0")
        os.system("iotkit-admin register Sound sound.v1.0")
        os.system("iotkit-admin register Temp temperature.v1.0")
        os.system("iotkit-admin register Flame flame.v1.0")
        print "Compiling Code..."
        os.system("i586-poky-linux-g++ -I/usr/include/upm -I/usr/include/mraa -O0 -g3 -Wall -c -fmessage-length=0 -m32 -march=i586 -c -ffunction-sections -fdata-sections -I/usr/include/mysql -L/usr/lib -lmysqlclient -lpthread -lz -lm -ldl -o ED-E.o ED-E.cpp")
        os.system("i586-poky-linux-g++ -lmraa -o ED-E ED-E.o -lupm-i2clcd -lupm-gas -lupm-yg1006 -lupm-groveloudness -lupm-buzzer -I/usr/include/mysql -L/usr/lib -lmysqlclient -lpthread -lz -lm -ldl")
        os.system("chmod 755 ED-E")
        print "Done."

    def logo(self):
        print '           ____                    _____                    _____          '
        print '         /\    \                  /\    \                  /\    \         '
        print '        /::\    \                /::\    \                /::\    \        '
        print '       /::::\    \              /::::\    \              /::::\    \       '
        print '      /::::::\    \            /::::::\    \            /::::::\    \      '
        print '     /:::/\:::\    \          /:::/\:::\    \          /:::/\:::\    \     '
        print '    /:::/__\:::\    \        /:::/  \:::\    \        /:::/__\:::\    \    '
        print '   /::::\   \:::\    \      /:::/    \:::\    \      /::::\   \:::\    \   '
        print '  /::::::\   \:::\    \    /:::/    / \:::\    \    /::::::\   \:::\    \  '
        print ' /:::/\:::\   \:::\    \  /:::/    /   \:::\ ___\  /:::/\:::\   \:::\    \ '
        print '/:::/__\:::\   \:::\____\/:::/____/     \:::|    |/:::/__\:::\   \:::\____\ '
        print '\:::\   \:::\   \::/    /\:::\    \     /:::|____|\:::\   \:::\   \::/    /'
        print ' \:::\   \:::\   \/____/  \:::\    \   /:::/    /  \:::\   \:::\   \/____/ '
        print '  \:::\   \:::\    \       \:::\    \ /:::/    /    \:::\   \:::\    \     '
        print '   \:::\   \:::\____\       \:::\    /:::/    /      \:::\   \:::\____\    '
        print '    \:::\   \::/    /        \:::\  /:::/    /        \:::\   \::/    /    '
        print '     \:::\   \/____/          \:::\/:::/    /          \:::\   \/____/     '
        print '      \:::\    \               \::::::/    /            \:::\    \         '
        print '       \:::\____\               \::::/    /              \:::\____\        '
        print '        \::/    /                \::/____/                \::/    /        '
        print '         \/____/                  ~~                       \/____/   '
        print '^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^'
        print '+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++'
        print '==========================================================================='
        print 'Home Automation System Setup ' + VERSION
        print '***************************************************************************'

if __name__ == "__main__":
    r = Install()
    r.install()
