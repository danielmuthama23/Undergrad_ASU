% CSE240 Fall 2021 HW14
% Tyler Fichiera
% Question 2

% Q2.1 - Rule to find toppings

/*
Max number of each topping to stay 
    Pepperoni (5 ounces):   9
    Meatballs (10 ounces):  4
    Basil (7 ounces):       6
    Olives (3 ounces):      15
    Chicken (8 ounces):     5
*/

% pizza/4
pizza(P, M, B, O, C) :-
    member(P, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]),
    member(M, [0, 1, 2, 3, 4]),
    member(B, [0, 1, 2, 3, 4, 5, 6]),
    member(O, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]),
    member(C, [0, 1, 2, 3, 4, 5]),
    W is 5*P + 10*M + 7*B + 3*O + 8*C,
    W =:= 45.

% Test cases (Q2.2-2.4):
% Expected output: `no`
q2 :- pizza(1, 2, 2, 2, 2).

/*
Expected output:
C = 3
M = 0
O = 3

C = 0
M = 0
O = 11

C = 1
M = 1
O = 5

C = 0
M = 3
O = 1
*/
q3 :-
    pizza(1, M, 1, O, C),
    write('C = '), write(C), nl,
    write('M = '), write(M), nl,
    write('O = '), write(O).

/*
Expected output:
B = 1
M = 0
O = 10
P = 0

B = 4
M = 0
O = 3
P = 0

B = 0
M = 1
O = 9
P = 0

B = 3
M = 1
O = 2
P = 0

B = 2
M = 2
O = 1
P = 0

B = 1
M = 3
O = 0
P = 0

B = 2
M = 0
O = 6
P = 1

B = 1
M = 1
O = 5
P = 1

B = 0
M = 2
O = 4
P = 1

B = 0
M = 0
O = 9
P = 2

B = 3
M = 0
O = 2
P = 2

B = 2
M = 1
O = 1
P = 2

B = 1
M = 2
O = 0
P = 2

B = 1
M = 0
O = 5
P = 3

B = 0
M = 1
O = 4
P = 3

B = 2
M = 0
O = 1
P = 4

B = 1
M = 1
O = 0
P = 4

B = 0
M = 0
O = 4
P = 5

B = 1
M = 0
O = 0
P = 6
*/
q4 :- pizza(P, M, B, O, 1),
    write('B = '), write(B), nl,
    write('M = '), write(M), nl,
    write('O = '), write(O), nl,
    write('P = '), write(P).
