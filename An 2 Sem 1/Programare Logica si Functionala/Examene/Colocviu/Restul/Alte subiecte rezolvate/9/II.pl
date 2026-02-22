% Functia returneaza un element dintr-o lista si lista dupa element
% candidat(L:list, E:int, R:list)
% L - lista de unde extragem
% E - elementul extras
% R - elementele dupa elementul extras
% model de flux: (i, o, o) -> Nedeterminist
% alte modele: (i, i, i), (i, i, o), (i, o, i), (o, i, i)
%
% model matematic:
% candidat(l1..ln) =
%   1. (l1, l2..ln), daca n >= 2 (Select)
%   2. candidat(l2..ln)          (Skip)
candidat([H|T], H, T).

candidat([_|T], E, R):-
    candidat(T, E, R).


% Functia construieste o submultime conform cerintei
% submultime(L:list, N:int, S:int, R:list)
% L - lista de numere disponibile
% N - numarul minim de elemente de adaugat
% S - suma elementelor curente
% R - submultimea rezultata
% model de flux: (i, i, i, o) -> Nedeterminist
% alte modele: (i, i, i, i)
%
% model matematic:
% submultime(l, n, s) =
%   1. [], daca n <= 0 si s mod 3 = 0
%   2. e (+) submultime(rez, n - 1, s + e)
%                        , unde (e, rez) = candidat(l)
subm(_, N, S, []):-
    N =< 0,
    S mod 3 =:= 0.

subm(L, N, S, [E|R]):-
    candidat(L, E, RestList),

    NewN is N - 1,
    NewS is S + E,

    subm(RestList, NewN, NewS, R).


% Functia returneaza toate submultimile conform cerintei
% subm_minim(L:list, N:int, R:list)
% model de flux: (i, i, o) -> Determinist
% alte modele: (i, i, i)
% L - lista de unde facem submultimile
% N - marimea minima a submultimilor
% R - toate astfel de submultimile posibile
%
% model matematic:
% subm_minim(l, n) = U { S | S apartine subm(l, n, 0) }
subm_minim(L, N, R):-
    findall(Rez, subm(L, N, 0, Rez), R).


