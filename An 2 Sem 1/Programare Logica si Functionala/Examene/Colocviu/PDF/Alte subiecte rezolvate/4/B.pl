% Functia lipeste lista L1 de lista L2
% my_append(L1: list, L2: list, R:list)
% model de flux: (i, i, o) -> Determinist
% L1 - prima lista
% L2 - a doua lista
% R - L2 concatenat pe L1
%
% model matematic:
% my_append(l1..ln, p) =
%    1. p, daca n = 0
%    2. l1 U my_append(l2..ln, p), altfel
my_append([], L, L).

my_append([H|T], L, [H|R]):-
    my_append(T, L, R).


% Functia verifica daca un element exista intr-o lista
% my_member(L:list, E:atom)
% model de flux: (i, i) -> Determinist
% L - lista in care ne uitam
% E - elementul dupa care ne uitam
%
% model matematic:
% my_member(l1..ln, e) =
%    1. false, daca n = 0
%    2. true, daca l1 = e
%    3. my_member(l2..ln), altfel
my_member([E|_], E):-!.

my_member([_|T], E):-
    my_member(T, E).


% Functia parseaza o lista liniara si construieste un arbore binar
% parse(List:list, Tree:arbore, Rest:list)
% model de flux: (i, o, o) -> Determinist
% L - lista input care incepe cu nodul curent si nr de descendenti
% T - structura arborelui construit (t(Val, Stanga, Dreapta))
% R - restul listei care a ramas neprocesat (pentru nodurile parinte)
%
% model matematic:
% parse(l1..ln) =
%    1. (t(l1, nil, nil), l3..ln), daca l2 = 0 (Frunza)
%    2. (t(l1, Left, nil), Rest), daca l2 = 1 (Are un copil)
%            , unde (Left, Rest) = parse(l3..ln)
%    3. (t(l1, Left, Right), Final), daca l2 = 2 (Are 2 copii)
%            , unde (Left, R1) = parse(l3..ln)
%              si (Right, Final) = parse(R1)
parse([Val, 0| Rest], t(Val, nil, nil), Rest).

parse([Val, 1| Rest], t(Val, Left, nil), FinalRest):-
   parse(Rest, Left, FinalRest).

parse([Val, 2 | Rest], t(Val, Left, Right), FinalRest):-
    parse(Rest, Left, RestAfterLeft),
    parse(RestAfterLeft, Right, FinalRest).


% Functia parcurge arborele si returneaza o lista de perechi
% collect(Tree:arbore, Level:integer, R:list)
% model de flux: (i, i, o) -> Determinist
% T - arborele curent
% Lvl - Nivelul curent (incepe de la 0)
% R - lista rezultat de forma [(lvl, val), ...]
%
% model matematic:
% collect(t1..tn, Lvl) =
%    1. [], daca n = 0
%    2. [(Lvl, Val)] U collect(Str, Lvl + 1) U collect(Dr, Lvl + 1)
%            , altfel, unde (Val, Str, Dr) = t1
collect(nil, _, []).

collect(t(Val, L, R), Level, [(Level, Val) | Rest]):-
    NextLevel is Level + 1,
    collect(L, NextLevel, ListL),
    collect(R, NextLevel, ListR),
    my_append(ListL, ListR, Rest).     % not allowed to use append


% Functia calculeaza suma valorilor, luand doar primul element de pe
%fiecare nivel
% sum_unique_levels(AllPairs:list, SeenLevels:list, S:integer)
% model de flux: (i, i, o) -> Determinist
% L - lista de perechi (Nivel, Valoare)
% Seen - lista nivelelor deja procesate
% S - suma finala
%
% model matematic:
% sum_unique(l1..ln, seen) =
%    1. 0, daca n = 0
%    2. val + sum_unique(l2..ln, seen U {lvl}),
%                              , daca lvl nu apartine seen
%                              , unde l1 = (lvl, val)
%    3. sum_unique(l2..ln, seen), altfel
sum_unique([], _, 0).

sum_unique([(Lvl, Val) | T], Seen, TotalSum):-
    \+ my_member(Seen, Lvl),         % not allowed to use member
    sum_unique(T, [Lvl | Seen], RestSum),
    TotalSum is Val + RestSum,
    !.

sum_unique([(_,_) | T], Seen, TotalSum):-
    sum_unique(T, Seen, TotalSum).


% Functia wrapper, le executa pe toate
% solve(List:list, R:integer)
% model de flux: (i, o) -> Determinist
% List - lista initiala
% R - suma primelor numere de pe fiecare nivel
%
% model matematic:
% sumTree(L) =
%    parse(L),
%    collect(T, 0), unde (T, R) = parse(L),
%    sum_unique(ListPairs, []), unde ListPairs = collect(T, 0)
sumTree(List, R):-
    parse(List, Tree, []),
    collect(Tree, 0, AllPairs),
    sum_unique(AllPairs, [], R).
