"""
Pda happano ej pda bhwc wna ajynulpaz ej pda owia swu wo pdeo iaoowca...
Here is your flag...
The a-zA-Z letters in the middle of curly brackets are converted in the same way as above.
pwn.365{WBzn2uG3ExPczthn4Bv3JLy8_ZL.0hJ5sYIsIvS}
"""
import string

# incorrect_msg = "Pda happano ej pda bhwc wna ajynulpaz ej pda owia swu wo pdeo iaoowca."
incorrect_msg = "WBzn2uG3ExPczthn4Bv3JLy8_ZL.0hJ5sYIsIvS"

lower = list(string.ascii_lowercase) + list(string.ascii_lowercase)
upper = list(string.ascii_uppercase) + list(string.ascii_uppercase)

difference = 4

correct_msg = ''

for ch in incorrect_msg:
    if ch.isalpha():
        if ch.islower():
            index = lower.index(ch)
            correct_msg += lower[index + difference]
        else:
            index = upper.index(ch)
            correct_msg += upper[index + difference]
    else:
        correct_msg += ch

print("pwn.365{" + correct_msg + "}")