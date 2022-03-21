"""
Your flag is in folder /tmp/digyourflag
The flag is seprated into two files
The final flag has a pair of curly brackets
Try to dig out your flag!
"""

# this python file should be in: /tmp

import os

directory = 'digyourflag'
 
flag = ['', '']

for filename in os.listdir(directory):
    f = os.path.join(directory, filename)
    for next_filename in os.listdir(f):
        fi = os.path.join(f, next_filename)
        if os.path.isfile(fi):
            with open(fi) as x:
                contents = x.read().strip()
                if contents.startswith('pwn'):
                    flag[0] = contents
                elif contents.endswith('}'):
                    flag[1] = contents

print("Flag:", "".join(flag))