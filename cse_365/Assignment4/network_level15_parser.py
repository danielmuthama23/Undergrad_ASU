IP = '67.178.80.83'

f = open('network_level15_output.txt', 'r')

lines = f.readlines()

flag = ''
for i in range(len(lines)):
    base_line = lines[i].strip()
    if IP in base_line:
        flag += lines[i + 2].strip()[-1]

print(flag)
        