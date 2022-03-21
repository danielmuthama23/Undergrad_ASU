"""
In this difficult challenge, your goal is to answer 50 questions correctly in 3 seconds about Mandatory Access Control (MAC).
The questions will randomly change every time.
It is very unlikely that you will be able to do this by hand (in fact, we would be very surprised if you did!.
The goal of this challenge is to write a program that can interact with this program to supply the correct answers.
The goal of this challenge is to write a program that can interact with this program to supply the correct answers.
The best hacker solution is to learn to use the Python pwntools library: https://docs.pwntools.com/en/stable/
Another approach would be to use the 'expect' family of libraries in your favorite programming language: https://en.wikipedia.org/wiki/Expect#Alternatives

Consider a MAC system with the following levels (from high to low):
Top Secret (TS)
Secret (S)
Confidential (C)
Unclassified (UC)

Also with the following categories:
Nuclear (NUC)
NATO (NATO)
Advanced Combat Engine (ACE)
Unidentified Flying Object (UFO)

Next, we'll ask a series of 50 yes or no questions about if a Subject with level X can read or write an Object with level Y
Get them all right, and get the flag

** This script doesn't work 100% of the time and I was too lazy to find the error case, but if you run it like 5 times, you're bound to get 100%.
"""
from pwn import *

LEVELS = ['UC', 'C', 'S', 'TS']
CATEGORIES = ['UFO', 'ACE', 'NATO', 'NUC']

def parse_question(question):
    verb = 'write' if 'write' in question else 'read'

    subject_level = question.split("Subject with level ")[1].split(" and cat")[0]
    subject_categories = question.split("gories {")[1].split("} " + verb)[0].replace(" ", "").split(",")

    object_level = question.split("Object with level ")[1].split(" and categories")[0]
    object_categories = question.split("categories {")[2].split("}?")[0].replace(" ", "").split(",")

    return [verb, subject_level, subject_categories, object_level, object_categories]

def solve_question(question):
    print(question)
    [verb, subject_level, subject_categories, object_level, object_categories] = parse_question(question)

    # check if operation happens in the correct order
    # reading = down, writing = up
    if verb == 'read':
        if LEVELS.index(subject_level) < LEVELS.index(object_level):
            return False
    else:
        if LEVELS.index(subject_level) > LEVELS.index(object_level):
            return False

    if verb == 'read':
        for oc in object_categories:
            if oc not in subject_categories:
                return False
    else:
        for sc in subject_categories:
            if sc not in object_categories:
                return False

    return True

if __name__ == "__main__":
    p = process('/challenge/midtermctf_MACAttack', stdin=PTY)

    txt = p.read().decode()
    question = txt.split('\n')[-2]

    for i in range(1, 51):
        answer = 'yes' if solve_question(question) else 'no'
        p.sendline(answer.encode())

        txt = p.read().decode()

        if 'Incorrect!' in txt:
            print(f'Question {i} incorrect!')
            break

        question = txt.split('\n')[-2]
        if 'flag' in question or 'pwn' in question:
            print(question)

print(p.read().decode())