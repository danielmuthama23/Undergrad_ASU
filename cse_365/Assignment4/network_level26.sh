# [INFO] This challenge will now perform a bunch of checks.
# [INFO] If you pass these checks, you will receive the flag.
# [INFO] This challenge will create a packet capture file in /tmp/find_flag.pcap and you will need to extract the flag from /tmp/find_flag.pcap .
# [INFO] The flag is sent in the tcp layer communication between source IP 70.203.1.7 and destination IP 252.215.211.240 and source port 58912 and destination port 38042
# [INFO] File written to /tmp/find_flag.pcap .
# [INFO] Good luck!

tcpdump -q -X -r /tmp/find_flag.pcap > network_level26_output.txt
