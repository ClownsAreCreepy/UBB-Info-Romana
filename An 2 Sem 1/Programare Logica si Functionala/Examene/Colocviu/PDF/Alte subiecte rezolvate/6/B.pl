% Functia proceseaza maximul intre 2 numere
% process_max(H:integer, LastMax:integer, Max:integer)
% model de flux: (i, i, o) -> Determinist
% H, LastMax - numerele pe care le comparam
% Max - maximul dintre ele
%
% model matematic:
% process_max(H, M) = | H, daca H > M
%                     | M, altfel

process_max(H, LastMax, Max):-
    H > LastMax, !,
    Max is H.

process_max(_, LastMax, Max):-
    Max is LastMax.


% Functia gaseste maximul dintr-o lista
% my_max(L:list, Max:integer)
% model de flux: (i, o) -> Determinist
% L - lista in care cautam
% Max - numarul maxim din lista
%
% model matematic:
% my_max(l1..ln) = | l1, daca n = 1
%                  | process_max(l1, M), unde M = my_max(l2..ln)

my_max([X], X):-!.

my_max([H|T], Max):-
    my_max(T, LastMax),
    process_max(H, LastMax, Max).


% Functia returneaza o sublista dintr-o lista
% get_sublist(L:list, Sub:list)
% model de flux: (i, o) -> Nedeterminist
% L - lista de unde extragem
% Sub - sublista pe care o extragem
%
% model matematic:
% get_sublist(l1..ln) = | l1, daca l1 e lista
%                       | get_sublist(l2..ln), altfel

get_sublist([H|_], H):-
    is_list(H).

get_sublist([_|T], Sub):-
    get_sublist(T, Sub).


% Functia calculeaza produsul a doua maxime din subliste
% calculate_pair(L1:list, L2:list, Prod:integer)
% model de flux: (i, i, o) -> Nedeterminist
% L1, L2 - listele de unde extragem sublistele
% Prod - produsul maximilor din sublistele extrase
%
% model matematic:
% calculate_pair(l2, l2) = M1 * M2
%                        , unde M1 = my_max(s1) si s1 = get_sublist(l1)
%                          si M2 = my_max(s2) si s2 = get_sublist(l2)
calculate_pair(L1, L2, Prod):-
    get_sublist(L1, S1),
    my_max(S1, M1),
    get_sublist(L2, S2),
    my_max(S2, M2),
    Prod is M1 * M2.


% Functia calculeaza produsul tuturor submultimilor a doua liste
% prod_sublist(L1:list, L2:list, R:list)
% model de flux: (i, i, o) -> Determinist
% L1, L2 - listele de unde extragem sublistele
% R - lista cu produsele tuturor maximelor sublistelor
%
% model matematic:
% prod_sublist(l1, l2) = U { P | P apartine calculate_pair(l1, l2) }

prod_sublist(L1, L2, R):-
    findall(Prod, calculate_pair(L1, L2, Prod), R).
