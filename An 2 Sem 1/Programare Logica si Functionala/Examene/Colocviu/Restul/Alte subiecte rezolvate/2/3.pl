subm_gen(_, 0, []):-!.

subm_gen([H|T], S, [H|R]):-
    S >= H,
    NewS is S - H,
    subm_gen(T, NewS, R).

subm_gen([_|T], S, R):-
    subm_gen(T, S, R).

subm_suma(L, S, R):-
    findall(Rez, subm_gen(L, S, Rez), R).
