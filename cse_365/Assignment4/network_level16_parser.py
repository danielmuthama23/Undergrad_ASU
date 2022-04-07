SOURCE_IP = '195.228.54.129.22580'
DEST_IP = '146.203.147.75'

f = open('network_level16_output.txt', 'r')

lines = f.readlines()

flag = ''
for i in range(len(lines)):
    base_line = lines[i].strip()
    if SOURCE_IP in base_line.split('>')[0] and DEST_IP in base_line.split('>')[1]:
        flag += lines[i + 2].strip()[-1]

print(flag)