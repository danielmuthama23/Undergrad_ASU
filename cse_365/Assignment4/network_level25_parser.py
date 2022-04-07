SOURCE_IP = '235.102.238.127'
DEST_IP = '150.106.19.143'

f = open('network_level25_output.txt', 'r')

lines = f.readlines()

for i in range(len(lines)):
    base_line = lines[i].strip()
    if SOURCE_IP in base_line.split('>')[0] and DEST_IP in base_line.split('>')[1] and 'tcp 25' in base_line:
        print(base_line)
        print(lines[i + 1].strip())
        print(lines[i + 2].strip())
        print(lines[i + 3].strip())
        print(lines[i + 4].strip())
        print(lines[i + 5].strip())
