f([], 0).

f([H|T], S):-
    f(T, S1),
    H < S1, !,
    S is H + S1.

f([_|T], S):-
    f(T, S1),
    S is S1 + 2.

% Folosim functie de procesare

f([], 0).

f([H|T], S):-
    f(T, S1),
    process(H, S1, S).

process(H, S1, S):-
    H < S1, !,
    S is H + S1.

process(_, S1, S):-
    S is S1 + 2.
