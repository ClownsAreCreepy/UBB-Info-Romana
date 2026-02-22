% Functia gaseste o submultime de N elemente cu suma para
% submultime(L:integer*, N:integer, CurrentSum:integer, Rest:integer*)
% model de flux: (i, i, i, o) -> Nedeterminist
% L - lista de unde alegem
% N - marimea submultimei
% CurrentSum - suma numerelor alese pana acum
% Rest - submultimea formata pana acum
%
% model matematic:
% submultime(l1..ln, N, CurrentSum):
%    1. [], daca N = 0 si CurrentSum % 2 = 0
%    2. l1 (+) submultime(l2..ln, n-1, CurrentSum + l1) (Alegem element)
%    3. submultime(l2..ln, n, CurrentSum) (Nu alegem element)
submultime(_, 0, CurrentSum, []):-
    CurrentSum mod 2 =:= 0,
    !.

submultime([H|T], N, CurrentSum, [H|Rest]):-
    N > 0,
    NewN is N - 1,
    NewSum is CurrentSum + H,
    submultime(T, NewN, NewSum, Rest).

submultime([_|T], N, CurrentSum, Rest):-
    N > 0,
    submultime(T, N, CurrentSum, Rest).



% Functia returneaza toate submultimile de N elemente cu suma para
% subm_suma(L:integer*, N:integer, R:list of list of integer)
% model de flux: (i, i, o) -> Determinist
% L - lista de unde luam submultimile
% N - nr de elemente al submultimilor
% R - lista cu toate submultimile posibile care satisfac condita
%
% model matematic:
% subm_suma(L, n) = U { S | S apartine submultime(L, n) }
subm_suma(L, N, R):-
    findall(Rez, submultime(L, N, 0, Rez), R).
