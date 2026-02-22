f([], -1).

f([H|T], S):-
    H > 0,
    f(T, S1),
    S1 < H, !,
    S is H.

f([_|T], S):-
    f(T, S1),
    S is S1.

% -> process result function

f([], -1).

f([H|T], S):-
    f(T, S1),
    process(H, S1, S).

process(H, S1, H):-
    H > 0,
    S1 < H, !.

process(_, S, S).

