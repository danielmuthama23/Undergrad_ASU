factorial(0,1).
factorial(N,F) :-
    N > 0,
    factorial(N-1, F1),
    F is N * F1.
