"""
Now let's encrypt a secret.
We have prepared the AES operations for you
keyexpansion, addroundkey, invmixcolumns, invsubbytes, and invshiftrows.
In this challenge, you need to write a program to call them properly.
The AES we use is 10 rounds with 128 bit keys.
https://www.commonlounge.com/discussion/e32fdd267aaa4240a4464723bc74d0a5 has decryption process.
WARNING: this challenging may cost you much efforts.
You should consider to skip this challenge if you cannot make it.
Your encoded encryption key is 435345333635207665727920636f6f6c
Your first part of the secret is encrypted as f985d78cb7b629f57279a852a400a167
Your second part of the flag is encrypted as c8b9f7ed8b8aa29fb0352f29e902518a
Your third part of the flag is encrypted as fd00c2d2e90d14a8a7b8bc8e623682c7
1. Inverse Shift Rows
2. Inverse Mix Columns
3. Inverse Substitution Bytes
4. Xor with Round Key
5. Expand Key
6. Submit Secret
7. Exit
Please enter your selection (between 1 and 7):
"""