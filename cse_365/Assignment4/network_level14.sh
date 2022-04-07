# [INFO] This challenge will now perform a bunch of checks.
# [INFO] If you pass these checks, you will receive the flag.
# [INFO] This challenge will create a packet capture file in /tmp/find_flag.pcap and you will need to extract the flag from /tmp/find_flag.pcap .
# [INFO] The flag is sent in the udp layer communication between source IP 43.196.247.30 and destination IP 212.200.151.202 and source port 42492 and destination port 17652
# [INFO] Note that there are a number of fake flags in this pcap, so you need to extract from only the given communication parameters.
# [INFO] File written to /tmp/find_flag.pcap .
# [INFO] Good luck!

tcpdump -q -X -r /tmp/find_flag.pcap > network_level14_output.txt
