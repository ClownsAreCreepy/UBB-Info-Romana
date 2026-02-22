% Functia insereaza un element pe o pozitie corecta dintr-o lista, sau
%nu daca e duplicata
% insert_ord(X:integer, L:list, R:list)
% model de flux: (i, i, o) -> Determinist
% X - elementul pe care il inseram
% L - lista initiala unde inseram
% R - lista rezultata dupa inserare
%
% model matematic:
% insert_ord(e, l1..ln) = | e, daca n = 0
%                         | e (+) l1..ln, daca X < H
%                         | l1..ln
%                         | l1 (+) insert_ord(e, l2..ln), daca X > H

insert_ord(X, [], [X]).

insert_ord(X, [H|T], [X, H|T]):-
    X < H.

insert_ord(X, [H|T], [H|T]):-
    X =:= H.

insert_ord(X, [H|T], [H|R]):-
    X > H,
    insert_ord(X, T, R).


% Functia sorteaza o lista
% my_sort(L:list, R:list)
% model de flux: (i, o) -> Determinist
% L - lista pe care o sortam
% R - lista initiala, sortata
%
% model matematic:
% my_sort(l1..ln) = | [], daca n = 0
%                   | insert_ord(l1, my_sort(l2..ln)), altfel

my_sort([], []).

my_sort([H|T], R):-
    my_sort(T, SortedTail),
    insert_ord(H, SortedTail, R).


% Functia creaza o submultime a elementelor unei liste
% submultime(L:list, R:list)
% model de flux: (i, o) -> Nedeterminist
% L - lista de unde luam elementele
% R - o submultime din L
%
% model matematic:
% submultime(l1..ln) = | [], daca n = 0
%                      | l1 (+) submultime(l2..ln), daca n > 0 (Select)
%                      | submultime(l2..ln), daca n > 0 (Skip)

submultime([], []).

submultime([H|T], [H|R]):-
    submultime(T, R).

submultime([_|T], R):-
    submultime(T, R).


% Functia creeaza o submultime de cel putin 2 elemente dintr-o lista
% get_solution(L:list, R:list)
% model de flux: (i, o) -> Nedeterminist
% L - lista de unde luam elementele
% R - o submultime din L cu cel putin 2 elemente
%
% model matematic:
% get_solution(l) = S, unde S = submultime(l) si |S| >= 2

get_solution(L, R):-
    submultime(L, R),
    R = [_, _|_].


% Functia returneza toate submultimile de cel putin 2 elemente
% subsir_cresc(L:list, R:list)
% model de flux: (i, o) -> Determinist
% L - lista de unde luam elementele
% R - toate submultimile de cel putin 2 elemente din L
%
% model matematic:
% subsir_cresc(l) = U { S | S apartine get_solution(l) }

subsir_cresc(L, R):-
    my_sort(L, Sorted), !,
    findall(Rez, get_solution(Sorted, Rez), R).
