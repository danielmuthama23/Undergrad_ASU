"""
After like level 26 I realized I could just write a generic script to solve the rest of them,
so I did and it saved me a lot of time.
"""

import subprocess

p = subprocess.Popen(['bash', 'base_level.sh'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
out, err = p.communicate()

print(out)

s_ip = str(out).split('between source IP ')[1].split(' and destination ')[0]
d_ip = str(out).split(' destination IP ')[1].split(' ')[0]

s_port = str(out).split(' source port ')[1].split(' and destination')[0]
d_port = str(out).split(' destination port ')[1].split('\\')[0]

SOURCE_IP = s_ip + '.' + s_port
DEST_IP = d_ip + '.' + d_port

print(SOURCE_IP)
print(DEST_IP)

f = open('base_output.txt', 'r')

lines = f.readlines()

flag = ''
previous = '___'
for i in range(len(lines)):
    base_line = lines[i].strip()
    if (
        (SOURCE_IP) in base_line.split('>')[0] and
        (DEST_IP) in base_line.split('>')[1] and
        'tcp 1' in base_line
    ):
        char = lines[i + 3].strip()[-1]
        if previous != char:
            flag += char
        previous = char

        # print(base_line)
        # print(lines[i + 1].strip())
        # print(lines[i + 2].strip())
        # print(lines[i + 3].strip())
        # print(lines[i + 4].strip())
        # print(lines[i + 5].strip())

print(flag)