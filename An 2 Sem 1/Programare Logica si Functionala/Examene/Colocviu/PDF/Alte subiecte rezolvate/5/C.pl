% Functia genereaza o submultime a unei liste cu suma numerelor para
% submultime(L:list, S:integer, R:list)
% model de flux: (i, i, o) -> Nedeterminist
% L - lista de unde formam subultimea
% S - suma curenta a numerelor
% R - submultimea curenta creata
%
% model matematic:
% submultime(l1..ln, s) = |
%                         |
%                         |
submultime([], S, []):-
    S mod 2 =:= 0.

submultime([H|T], S, [H|R]):-
    NewS is S + H,
    submultime(T, NewS, R).

submultime([_|T], S, R):-
    submultime(T, S, R).

% Functia main, genereaza toate submultimile cu suma numerelor para
% subm_sum(L:list, R:list)
% model de flux: (i, o) -> Determinist
% L - lista de unde formam submultimile
% R - toate submultimile gasite cu suma numerelor para
%
% model matematic:
% subm_sum(l1..ln) = U{S | S apartine submultime(l1..ln, 0)}
subm_sum(L, R):-
    findall(Rez,submultime(L, 0, Rez), R).

