from cc.udp import UDP
import numpy as np


RECV_ADDR = ("0.0.0.0", 8080)
SEND_ADDR = ("127.0.0.1", 8181)

udp = UDP(recv_addr=RECV_ADDR, send_addr=SEND_ADDR)



udp.send(b"\x05\x06\x07\x08")

udp.send(b"\x01\x02\x03\x04")

print(udp.recv())

