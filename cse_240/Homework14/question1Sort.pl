% CSE240 Fall 2021 HW14
% Tyler Fichiera
% Question 1

% Q1.1 - Get last element rule

% get_last/2
get_last([E], E).
get_last([_|T], E) :- get_last(T, E).

% Test case:
% Expected output: `E = y`
q1 :- get_last([a, b, c, x, y], E), write('E = '), write(E).

% Q1.2 - Remove last element rule

% remove_last/2
remove_last([_], []).
remove_last([H|T1], [H|T2]) :- remove_last(T1, T2).

% Test case:
% Expected output: `Ls = [a, b, c, x]`
q2 :- remove_last([a, b, c, x, y], Ls), write('Ls = '), write(Ls).

% Q1.3 - Quicksort rule

% split/4
% stopping condition
split(_,[],[],[]).
% take first from T and put it into Le
split(Pivot, [X|T], [X|Le], Gt):-
    X =< Pivot, split(Pivot, T, Le, Gt).
% take first from T and put it into Gt
split(Pivot, [X|T], Le, [X|Gt]):-
    X > Pivot, split(Pivot, T, Le, Gt).

% qsort/2
qsort([], []) :- !.
% returns `Sorted` which is `L1` in increasing order
qsort(L1, Sorted) :-
    get_last(L1, Pivot),
    remove_last(L1, T),
    split(Pivot, T, L2, L3),
    qsort(L2, S1), % sort the first part
    qsort(L3, S2), % sort the second part
    append(S1, [Pivot|S2], Sorted).

% Test case:
% Expected output: `Sorted = [1, 3, 4, 4, 6, 6, 8, 9, 12, 22, 25]`
q3 :-
    qsort([8, 3, 4, 12, 25, 4, 6, 1, 9, 22, 6], Sorted),
    write('Sorted = '),
    write(Sorted).
