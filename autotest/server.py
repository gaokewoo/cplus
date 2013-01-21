#!/usr/bin/env python
import socket

if __name__ == '__main__':
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(('localhost', 8888))
    sock.listen(5)
    while True:
        connection,address = sock.accept()
        while True:
            try:
                connection.settimeout(15)
                buf = connection.recv(10240)
                if not buf:
                    break
                print "Server receive data:" + buf
                connection.send('ab<?xml version="1.0" encoding="UTF-8"?><SequenceNum>1</SequenceNum><ReqSeqNum>1006</ReqSeqNum><as>123</as><bs>456</bs>')
            except socket.timeout:
                print 'time out'
                connection.close()
        connection.close()
    sock.close()
    print "done"

