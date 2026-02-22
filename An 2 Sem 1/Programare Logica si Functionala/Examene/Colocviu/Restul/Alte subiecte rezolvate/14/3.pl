% Functie care returneaza un element dintr-o lista si lista dupa
% candidat(L:list, E:int, R:list)
% L - lista de unde extragem
% E - elementul extras
% R - elementele dupa elementul extras
% model de flux: (i, o, o) -> Nedeterminist
% alte modele: (i, i, i), (i, i, o), (i, o, i), (o, i, i)
%
% model matematic:
% candidat(l1..ln) =
%   1. (l1, l2..ln), daca n >= 1    (Select)
%   2. candidat(l2..ln), daca n >= 1(Skip)
candidat([H|T], H, T).

candidat([_|T], E, R):-
    candidat(T, E, R).


% Functie care creaza o combinare de K elemente cu suma para
% comb(L:list, K:int, S:int, R:list)
% L - lista din care extragem
% K - nr de elemente care mai trebuie adaugate in combinare
% S - suma elementelor
% R - combinarea curenta
% model de flux: (i, i, i, o) -> Nedeterminist
% alte modele: (i, i, i, i)
%
% model matematic:
% comb(l, k, s) =
%   1. [], daca k = 0 si s % 2 = 0
%   2. e (+) comb(rez, k - 1, s + e), unde (e, rez) = candidat(l)
comb(_, 0, S, []):-
    S mod 2 =:= 0.

comb(L, K, S, [E|R]):-
    K > 0,
    candidat(L, E, RestList),

    NewK is K - 1,
    NewS is S + E,

    comb(RestList, NewK, NewS, R).


% Functie care returneaza toate combinarile de K elemente cu suma para
% comb_par(L:list, K:int, R:list)
% L - lista din care extragem
% K - marimea combinarilor
% R - lista cu toate aranjamentele de K elemente cu suma para
% model de flux: (i, i, o) -> Nedeterminist
% alte modele: (i, i, i)
%
% model matematic:
% comb_par(l, k) = U { C | C apartine comb(l, k, 0) }
comb_par(L, K, R):-
    findall(Rez, comb(L, K, 0, Rez), R).
