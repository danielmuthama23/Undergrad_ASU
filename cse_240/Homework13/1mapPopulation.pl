% CSE240 Fall 2021 HW13
% Tyler Fichiera
% Question 1

% Q1.1 - Edge facts

% edge/2
edge(wa, id).
edge(wa, or).

edge(or, wa).
edge(or, id).
edge(or, nv).
edge(or, ca).

edge(ca, or).
edge(ca, nv).
edge(ca, az).

edge(id, wa).
edge(id, or).
edge(id, nv).
edge(id, ut).
edge(id, wy).
edge(id, mt).

edge(nv, or).
edge(nv, id).
edge(nv, ut).
edge(nv, az).
edge(nv, ca).

edge(ut, id).
edge(ut, wy).
edge(ut, co).
edge(ut, az).
edge(ut, nv).

edge(az, ca).
edge(az, nv).
edge(az, ut).
edge(az, nm).

edge(mt, id).
edge(mt, wy).
edge(mt, nd).
edge(mt, sd).

edge(wy, id).
edge(wy, mt).
edge(wy, sd).
edge(wy, ne).
edge(wy, co).
edge(wy, ut).

edge(co, ut).
edge(co, wy).
edge(co, ne).
edge(co, ks).
edge(co, ok).
edge(co, nm).

edge(nm, az).
edge(nm, co).
edge(nm, ok).
edge(nm, tx).

edge(nd, mt).
edge(nd, sd).

edge(sd, nd).
edge(sd, mt).
edge(sd, wy).
edge(sd, ne).

edge(ne, sd).
edge(ne, wy).
edge(ne, co).
edge(ne, ks).

edge(ks, co).
edge(ks, ne).
edge(ks, ok).

% additional states: texas, oklahoma, arkansas, louisiana, mississippi
edge(tx, nm).
edge(tx, ok).
edge(tx, ar).
edge(tx, la).

edge(ok, tx).
edge(ok, nm).
edge(ok, co).
edge(ok, ks).
edge(ok, ar).

edge(ar, ok).
edge(ar, tx).
edge(ar, la).
edge(ar, ms).

edge(la, tx).
edge(la, ar).
edge(la, ms).

edge(ms, ar).
edge(ms, la).

% Q1.2 - Color facts

% color/2
color(wa, yellow).
color(or, red).
% ca should be green to prevent conflict with yelllow nevada
color(ca, yellow).
color(id, orange).
color(nv, yellow).
color(ut, red).
color(az, orange).
color(mt, green).
color(wy, yellow).
color(co, orange).
color(nm, green).
% nd should be yellow to prevent conflict with green montana
color(nd, green).
color(sd, orange).
color(ne, red).
color(ks, green).
color(tx, orange).
color(ok, red).
color(ar, green).
color(la, yellow).
color(ms, orange).

% Q1.3 - Population facts

% population/2
population(wa, 8).
population(or, 4).
population(ca, 40).
population(id, 2).
population(nv, 3).
population(ut, 3).
population(az, 8).
population(mt, 1).
population(wy, 1).
population(co, 6).
population(nm, 2).
population(nd, 1).
population(sd, 1).
population(ne, 2).
population(ks, 3).
population(tx, 30).
population(ok, 4).
population(ar, 3).
population(la, 5).
population(ms, 3).

% Q1.4 - Miscolored rule

% I am not using an adjacent rule since I defined
% the edge facts in both directions.
% Example: I have edge(ca, az) and edge(az, ca)
miscolor(S1, S2, Color) :-
    edge(S1, S2),
    color(S1, Color),
    color(S2, Color).

% Q1.5 - Total population rule

totalpopulation([], 0).
% use anon variable to prevent singleton variable warning
totalpopulation([[_, Population]|Tail], Total) :-
    totalpopulation(Tail, Total1),
    Total is Total1 + Population.

% Test cases:
q1 :- miscolor(S1, S2, Color),
    write(S1), write(' and '), write(S2),
    write(' have conflict color: '), write(Color),
    nl,
    totalpopulation(
        [[az, 7], [ca, 40], [ne, 3], [ut, 3], [or, 4], [id, 2], [wy, 1], [sd, 1], [tx, 30]],
        Total
    ), write('Total = '), write(Total),
    nl.
