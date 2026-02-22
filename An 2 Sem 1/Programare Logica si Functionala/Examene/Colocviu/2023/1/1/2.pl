f([], -1).

f([H|T], S):-
    f(T, S1),
    process(S, S1, H).

process(S, S1, H):-
    H>0,
    S1 < H, !,
    S is H.

process(S1, S1, _).
