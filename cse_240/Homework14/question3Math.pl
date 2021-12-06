% CSE240 Fall 2021 HW14
% Tyler Fichiera
% Question 3

/*
recursive piecewise func:
    if y ≤ 0:
        x
    if x ≤ 0:
        y
    if x ≥ y:
        x + foo(x - 1, y - 2)
    if x < y:
        y + foo(x - 2, y - 3)
*/

% Step 1: form the size-n problem
% foo(X, Y, F) F is used to store the value of foo(X, Y)

% Step 2: the stopping criteria
% if if y ≤ 0, x:
foo(X, Y, F) :-
    Y =< 0,
    F is X.
% if x ≤ 0, y:
foo(X, Y, F) :-
    X =< 0,
    F is Y.

% Step 3: size n problem
% if X ≥ Y:
%   foo(X - 1, Y - 2, F1)
% if X < Y:
%   foo(X - 2, Y - 3, F2)

% Step 4: Solve size n problem with size m problem
% if X ≥ Y: F is X + F1
foo(X, Y, F) :-
    X >= Y,
    A1 is X - 1,
    A2 is Y - 2,
    foo(A1, A2, F1),
    F is X + F1.
% if X < Y: F is Y + F2
foo(X, Y, F) :-
    X < Y,
    A1 is X - 2,
    A2 is Y - 3,
    foo(A1, A2, F2),
    F is Y + F2.

% Test case:
% Expected output: `F = 12`
q3 :-
    foo(5, 6, F),
    write('F = '),
    write(F).
