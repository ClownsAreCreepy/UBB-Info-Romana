prim(N, D):-
    N < D * D.

prim(N, D):-
    N mod D =\= 0,
    NextD is D + 1,
    prim(N, NextD).


check_prim(2):-!.

check_prim(N):-
    N > 2,
    N mod 2 =:= 1,
    prim(N, 3).

elim_prim(L, 0, L):-!.

elim_prim([H|T], N, R):-
    check_prim(H), !,
    NewN is N - 1,
    elim_prim(T, NewN, R).

elim_prim([H|T], N, [H|R]):-
    elim_prim(T, N, R).
