f([], 0).
f([H|T], S):-
    f(T, S1),
    process(H, S1, S).

process(H, S1, S):-
    S1 < H, !,
    S is H.

process(_, S1, S):-
    S is S1.
