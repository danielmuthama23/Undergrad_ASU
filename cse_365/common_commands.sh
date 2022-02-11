# !/bin/bash

# generate ssh key
ssh-keygen -t rsa

# login to server
ssh -i /Users/tylerfichiera/.ssh/id_rsa hacker@pwn.cse365.io

# make .sh file executable
chmod +x ./common_commands.sh
