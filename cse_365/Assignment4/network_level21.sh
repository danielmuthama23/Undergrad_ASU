# [INFO] This challenge will now perform a bunch of checks.
# [INFO] If you pass these checks, you will receive the flag.
# [INFO] This challenge will create a packet capture file in /tmp/find_flag.pcap and you will need to extract the flag from /tmp/find_flag.pcap .
# [INFO] The flag is sent in the tcp layer communication between source IP 249.41.226.217 and destination IP 42.217.43.118 and source port 46231 and destination port 7746
# [INFO] Note that there are a number of fake flags in this pcap, so you need to extract from only the given communication parameters.
# [INFO] File written to /tmp/find_flag.pcap .
# [INFO] Good luck!

tcpdump -q -X -r /tmp/find_flag.pcap > network_level21_output.txt