% Functie care returneaza un element dintr-o lista si lista dupa element
% candidat(L:list, E:int, R:list)
% L - lista de unde extragem
% E - elementul extras
% R - elementele dupa elementul extras
% model de flux: (i, o, o) -> Nedeterminist
% alte modele: (i, i, i), (i, i, o), (i, o, i), (o, i, i)
%
% model matematic:
% candidat(l1..ln) =
%   1. (l1, l2..ln), daca n >= 1 (Select)
%   2. candidat(l2..ln), daca n >= 1  (Skip)
candidat([H|T], H, T).

candidat([_|T], E, R):-
    candidat(T, E, R).

% Functie care creaza submultime cu suma divizibila cu 3
% subm(L:list, N:int, S:int, R:list)
% L - lista din care extragem
% N - nr de elemente care trebuie adaugate in submultime
% S - suma actuala a nr din submultime
% R - submultimea curenta
% model de flux: (i, i, i, o) -> Nedeterminist
% alte modele: (i, i, i, i)
%
% model matematic:
% subm(l, n, s) =
%    1. [], daca n <= 0 si s % 3 = 0
%    2. e (+) subm(rez, n - 1, s + e), unde (e, rez) = candidat(l)
subm(_, N, S, []):-
    N =< 0,
    S mod 3 =:= 0.

subm(L, N, S, [E|R]):-
    candidat(L, E, Rez),

    NewN is N - 1,
    NewS is S + E,

    subm(Rez, NewN, NewS, R).


% Functie care returneaza toate submultimile cu suma divizibila cu 3
% subm_div(L:list, R:list)
% L - lista din care extragem
% R - lista cu toate submultimile de cel putin un element posibile
% model de flux: (i, o) -> Nedeterminist
% alte modele: (i, i)
%
% model matematic:
% subm_div(l) = U { S | S apartine subm(l, 1, 0) }
subm_div(L, R):-
    findall(Rez, subm(L, 1, 0, Rez), R).
