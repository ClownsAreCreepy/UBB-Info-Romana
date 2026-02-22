f([], 0).
f([H|T], S):-
    f(T, S1),
    process(H, S1, S).

process(H, S1, S):-
    S1 > 2, !,
    S is S1 + H.

process(_, S1, S):-
    S is S1 + 1.
