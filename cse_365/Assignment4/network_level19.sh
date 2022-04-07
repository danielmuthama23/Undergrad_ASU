# [INFO] This challenge will now perform a bunch of checks.
# [INFO] If you pass these checks, you will receive the flag.
# [INFO] This challenge will create a packet capture file in /tmp/find_flag.pcap and you will need to extract the flag from /tmp/find_flag.pcap .
# [INFO] The flag is sent in the tcp layer communication between source IP 58.108.161.15 and destination IP 144.49.53.243 and source port 50333 and destination port 42877
# [INFO] File written to /tmp/find_flag.pcap .
# [INFO] Good luck!

tcpdump -q -X -r /tmp/find_flag.pcap > network_level19_output.txt
