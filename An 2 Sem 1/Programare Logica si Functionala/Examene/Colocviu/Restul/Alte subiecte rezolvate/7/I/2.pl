f([], 0).

f([H|T], S):-
    f(T, S1),
    S1 < H, !,
    S is H.

f([_|T], S):-
    f(T, S1),
    S is S1.

% -> folosim functie auxiliara

f([], 0).

f([H|T], S):-
    f(T, S1),
    process(H, S1, S).

process(H, S1, H):-
    S1 < H, !.

process(_, S, S).

