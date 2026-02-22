% Functia genereaza o lista cu numere de la A la B
% generam_lista(A:int, B:int, R:list)
% A - capatul inferior al listei
% B - capatul superior al listei
% R - lista rezultata
% model de flux: (i, i, o) -> Determinist
% alte modele: (i, i, i), (i, o, i), (o, i, i), (o, o, i)
%
% model matematic:
% generam_lista(a, b) = | (B), daca a = b
%                       | a (+) generam_lista(a + 1, b), altfel
generam_lista(B, B, [B]):-!.

generam_lista(A, B, [A|R]):-
    NewA is A + 1,
    generam_lista(NewA, B, R).

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

% Functie care creaza submultime cu suma para
% subm(L:list, K:int, S:int, R:list)
% L - lista din care extragem
% K - nr de elemente care mai trebuie adaugate in submultime
% S - suma actuala a nr din submultime
% R - submultimea curenta
% model de flux: (i, i, i, o) -> Nedeterminist
% alte modele: (i, i, i, i)
%
% model matematic:
% subm(l, n, s) =
%    1. [], daca k = 0 si s % 2 = 0
%    2. e (+) subm(rez, n - 1, s + e), unde (e, rez) = candidat(l)
subm(_, 0, S, []):-
    S mod 2 =:= 0.

subm(L, N, S, [E|R]):-
    candidat(L, E, Rez),

    NewN is N - 1,
    NewS is S + E,

    subm(Rez, NewN, NewS, R).


% Functie returneaza dintr-un interval toate submultimile cu suma para
% subm_par(A:int, B:int, K:int, R:list)
% A: capatul inferior al intervalului
% B: capatul superior al intervalului
% K: marimea submultimilor
% R - lista cu toate submultimile de cel putin un element posibile
% model de flux: (i, i, i, o) -> Determinist
% alte modele: (i, i, i, i)
%
% model matematic:
% subm_par(a, b, k) = U { S | S apartine subm(generam_lista(a, b), k) }
subm_par(A, B, K, R):-
    generam_lista(A, B, L),
    findall(Rez, subm(L, K, 0, Rez), R).
