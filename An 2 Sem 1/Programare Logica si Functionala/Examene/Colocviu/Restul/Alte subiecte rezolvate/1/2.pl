% Returneaza un element dintr-o lista si lista fara element
% candidat(L:integer*, E:integer, R:integer*)
% model de flux: (i, o, o) -> Nedeterminist
% L - lista de unde extragem
% E - elementul pe care il extragem
% R - lista rezultat, fara elementul extras
%
% model matematic:
% candidat(l1..ln) =
%    1. (l1, l2..ln)
%    2. (e, e (+) rez), unde (e, rez) apartin candidat(l1..ln)
candidat([E|T], E, T).

candidat([H|T], E, [H|R]):-
    candidat(T, E, R).


% Alege primul element din lista
% permutare(L:integer*, P:integer*)
% model de flux: (i, o) -> Nedeterminist
% L - lista de elemente pe care o permutam
% P - permutarea curenta a listei
%
% model matematic:
% permutare(l1..ln) =
%    candidat(l1..ln)
%    perm_aux(Rest, H), unde (H, Rest) apartin candidat(l1..ln)
permutare(L, [H|T]):-
    candidat(L, H, Rest),
    perm_aux(Rest, H, T).


% Ia elementele urmatoare pentru permutare si verifice sa fie ok
% perm_aux(L:integer*, OldVal:integer, R:integer*)
% model de flux: (i, i, o)
% L - lista de unde luam elemente
% OldVal - ultima valoare adaugata in permutare
% R - permutarea curenta
%
% model matematic:
% perm_aux(l1..ln, OldVal) =
%    1. [], daca n = 0
%    2. E (+) perm_aux(RestList, E)
%                     , daca |E - OldVal| <= 3
%                     , unde (E, RestList) = candidat(l1..ln)
perm_aux([], _, []).

perm_aux(L, OldVal, [E|R]):-
    candidat(L, E, Rest),
    D is abs(E - OldVal),
    D =< 3,
    perm_aux(Rest, E, R).



% Functia returneaza o lista cu toate permutarile posibile, unde
%elementele alaturate au diferenta in modul mai mica ca 3
% mai_mic_trei(L:integer*, R:list of list of integer)
% model de flux: (i, o) -> Determinist
% L - lista din care formam permutarile
% R - lista de permutari posibile care respecta conditia impusa
%
% model matematic:
% mai_mic_trei(L) = U{ S | S apartine permutari(L) }
mai_mic_trei(L, R):-
    findall(Rez, permutare(L, Rez), R).













