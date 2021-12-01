% CSE240 Fall 2021 HW13
% Tyler Fichiera
% Question 3

/*
recursive piecewise func:
    if y ≤ 0:
        x + 1
    if x ≤ 0:
        y + 1
    if x < y:
        x + 2 + foo(x - 2, y)
    if x ≥ y:
        y + 3 + foo(x, y - 3)
*/

% Step 1: form the size-n problem
% foo(X, Y, Z) Z is used to store the value of foo(X, Y)

% Step 2: the stopping criteria
% if y ≤ 0, x + 1:
foo(X, Y, X + 1) :-
    Y =< 0.
% if x ≤ 0, y + 1:
foo(X, Y, Y + 1) :-
    X =< 0.

% Step 3: size n problem
% if X < Y:
%   foo(X - 2, Y, Z1)
% if x ≥ y:
%   foo(X, Y - 3, Z2)

% Step 4: Solve size n problem with size m problem
% if X < Y: Z is X + 2 + Z1
foo(X, Y, Z) :-
    X > 0,
    Y > 0,
    X < Y,
    foo(X - 2, Y, Z1),
    Z is X + 2 + Z1.
% if X >= Y: Z is Y + 3 + Z2
foo(X, Y, Z) :-
    X > 0,
    Y > 0,
    X >= Y,
    foo(X, Y - 3, Z2),
    Z is Y + 3 + Z2.

% Test case:
q3 :-
    foo(5, 6, Z),
    write(Z),
    nl.
