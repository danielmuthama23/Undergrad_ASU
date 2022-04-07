SOURCE_IP = '51.21.138.238'
DEST_IP = '66.249.199.34'

f = open('network_level23_output.txt', 'r')

lines = f.readlines()

for i in range(len(lines)):
    base_line = lines[i].strip()
    if SOURCE_IP in base_line.split('>')[0] and DEST_IP in base_line.split('>')[1] and 'tcp 50' in base_line:
        print(base_line)
        print(lines[i + 1].strip())
        print(lines[i + 2].strip())
        print(lines[i + 3].strip())
        print(lines[i + 4].strip())
        print(lines[i + 5].strip())
        print(lines[i + 6].strip())
