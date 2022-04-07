import socket, json

PORT = 1302

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((socket.gethostname(), PORT))
s.sendall(b'*')

while True:
    part = s.recv(4096)
    if not part:
        break # either 0 or end of data
    print(part)

s.close()
