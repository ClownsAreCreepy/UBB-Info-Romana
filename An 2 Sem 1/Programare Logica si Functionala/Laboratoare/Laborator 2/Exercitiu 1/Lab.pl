% is_in(E: Intreg, L: Lista de Intreg)
% model de flux: is_in(i, i)
% E - elementul pe care il cautam in lista
% L1 - lista in care cautam elementul

is_in(E, [E|_]):- !.
is_in(E, [_|T]):-
    is_in(E, T).


%dif(L1: Lista de Intreg, L2: Lista de Intreg, R: Lista de Intreg)
% model de flux: dif(i,i,o)
% L1 - lista "descazatoare", adica cea din care luam elemente
% L2 - lista "descazuta", adica cea din care nu trebuie sa luam elemente
% R - lista dezultata din scaderea lui L2 din L1

dif([], _, []):- !.

dif([H|T], L2, R):-
    is_in(H, L2),
    dif(T, L2, R),
    !.

dif([H|T], L2, [H|R]):-
    dif(T, L2, R).


% add(L: Lista de Intreg, R: Lista de Intreg)
% model de flux: add(i,o)
% L - lista initiala
% R - lista initiala, dar cu un 1 dupa fiecare numar par

add([], []):- !.

add([H|T], [H, 1|R]):-
    H mod 2 =:= 0,
    add(T, R),
    !.

add([H|T], [H|R]):-
    add(T, R).









