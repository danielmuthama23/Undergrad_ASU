# [INFO] This challenge will now perform a bunch of checks.
# [INFO] If you pass these checks, you will receive the flag.
# [INFO] This challenge will create a packet capture file in /tmp/find_flag.pcap and you will need to extract the flag from /tmp/find_flag.pcap .
# [INFO] The flag is sent in the tcp layer communication between source IP 86.150.92.242 and destination IP 143.2.237.83 and source port 12641 and destination port 7551
# [INFO] File written to /tmp/find_flag.pcap .
# [INFO] Good luck!

tcpdump -q -X -r /tmp/find_flag.pcap > network_level20_output.txt