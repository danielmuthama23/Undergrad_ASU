"""
In this challenge, you will implement the addroundkey script by yourself.
The idea of addroundkey is straightforward.
You take two values, a state and a round key, convert them to matrices,
and xor the two elements from each matrix.
Check https://en.wikipedia.org/wiki/Advanced_Encryption_Standard#The_AddRoundKey_step
You will get 1/3 secret if you run your addroundkey with the round key and a state.
Your secret starts with 365.
Your round key is 435345333635207665727920636f6f6c
Your first state is 7065704874774e2c1c023e48060d5b3a
Your second state is 3a1614057000703551454a182e393526
Your third state is 161d2776434d72425c4b1d5929172211
"""

states = [
    "7065704874774e2c1c023e48060d5b3a",
    "3a1614057000703551454a182e393526",
    "161d2776434d72425c4b1d5929172211"
]

round_key = "435345333635207665727920636f6f6c"

def add_round_key(state, roundKey):
    secret = ""

    for i in range(0, len(state), 2):
        str1 = state[i:i+2]
        str2 = roundKey[i:i+2]
        subkey = hex(int(str1, 16) ^ int(str2, 16))

        secret += str(subkey).replace("0x", "")

    return secret

def main():
    concat_secrets = ""
    for state in states:
        concat_secrets += add_round_key(state, round_key)
    
    print(concat_secrets)
    # then paste concat_secrets into https://onlinestringtools.com/convert-bytes-to-string

main()
