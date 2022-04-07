SOURCE_IP = '43.196.247.30'
DEST_IP = '212.200.151.202'

f = open('network_level14_output.txt', 'r')

lines = f.readlines()

for i in range(len(lines)):
    base_line = lines[i].strip()
    if SOURCE_IP in base_line.split('>')[0] and DEST_IP in base_line.split('>')[1]:
        flag_part = "".join([
            lines[i + 1].strip().split("  ")[-1],
            lines[i + 2].strip().split("  ")[-1],
            lines[i + 3].strip().split("  ")[-1],
            lines[i + 4].strip().split("  ")[-1],
        ])
        print(flag_part)
