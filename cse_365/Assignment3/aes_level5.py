"""
In this challenge, you will implement *inverse* row shifting.
You will get 1/3 secret if you run the correct implementation with a state.
You need to make it correct for three times.
Check this link: https://en.wikipedia.org/wiki/Advanced_Encryption_Standard#The_ShiftRows_step.
Your first state is 33456c6d644f7a7b774a356663367170
Your second state is 34694e314e35657879724a494f513837
Your third state is 7270647d344d716f724e30436538464e
"""

import collections
from operator import inv

states = [
    "33456c6d644f7a7b774a356663367170",
    "34694e314e35657879724a494f513837",
    "7270647d344d716f724e30436538464e"
]

"""
example: 33456c6d644f7a7b774a356663367170 ->
[
    ['33', '45', '6c', '6d'],
    ['64', '4f', '7a', '7b'],
    ['77', '4a', '35', '66'],
    ['63', '36', '71', '70']
]
"""
def create_matrix(state):
    matrix = []

    current_row = []
    for i in range(0, len(state), 2):
        if i % 8 == 0 and i > 0:
            matrix.append(current_row)
            current_row = []

        current_row.append(state[i:i+2])

    matrix.append(current_row)

    return matrix

"""
[
    ['33', '45', '6c', '6d'],
    ['64', '4f', '7a', '7b'],
    ['77', '4a', '35', '66'],
    ['63', '36', '71', '70']
] ->
[
    ['33', '64', '77', '63'],
    ['45', '4f', '4a', '36'],
    ['6c', '7a', '35', '71'],
    ['6d', '7b', '66', '70']
]
credit: https://www.programiz.com/python-programming/examples/transpose-matrix
"""
def transpose_matrix(matrix):
    return [[matrix[j][i] for j in range(len(matrix))] for i in range(len(matrix[0]))]

"""
[
    ['33', '64', '77', '63'],
    ['45', '4f', '4a', '36'],
    ['6c', '7a', '35', '71'],
    ['6d', '7b', '66', '70']
] ->
[
    ['33', '64', '77', '63'],
    ['36', '45', '4f', '4a'],
    ['35', '71', '6c', '7a'],
    ['7b', '66', '70', '6d']
]
"""
def inverse_shift(matrix):
    for r in range(0, len(matrix)):
        collection = collections.deque(matrix[r])
        collection.rotate(r)
        matrix[r] = list(collection)

    return matrix

"""
retranspose step:
[
    ['33', '64', '77', '63'],
    ['4f', '4a', '36', '45'],
    ['35', '71', '6c', '7a'],
    ['70', '6d', '7b', '66']
] ->
[
    ['33', '4f', '35', '70'],
    ['64', '4a', '71', '6d'],
    ['77', '36', '6c', '7b'],
    ['63', '45', '7a', '66']
]
"""

def flatten_matrix(matrix):
    flat_str = ""

    for x in matrix:
        for y in x:
            flat_str += y
    
    return flat_str

def main():
    concat_secrets = ""

    for state in states:
        matrix = create_matrix(state)
        transposed_matrix = transpose_matrix(matrix)
        inverse = inverse_shift(transposed_matrix)
        retransposed_matrix = transpose_matrix(inverse)
        flat_matrix = flatten_matrix(retransposed_matrix)
        concat_secrets += flat_matrix

    print(concat_secrets)
    # then paste concat_secrets into https://onlinestringtools.com/convert-bytes-to-string

main()
