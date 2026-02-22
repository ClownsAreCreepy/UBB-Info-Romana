% Functia genereaza o lista cu numere de la M la 2 * N - 1
% generam_lista(M:int, N:int, R:list)
% M - numarul de unde incepem adaugarea
% N - numarul dupa care terminam adaugarea
% R - lista rezultata
% model de flux: (i, i, o) -> Determinist
% alte modele: (i, i, i)
%
% model matematic:
% generam_lista(M, N) =
%   1. (M), daca M = N * 2 - 1
%   2. M (+) generam_lista(M + 1, N)

generam_lista(M, N, [M]):-
    M =:= N * 2 - 1, !.

generam_lista(M, N, [M|R]):-
    M1 is M + 1,
    generam_lista(M1, N, R).


% Functia returneaza un element dintr-o lista si lista fara element
% candidat(L:list, E:int, R:list)
% L - lista de unde extragem
% E - elementul extras
% R - lista fara element
% model de flux: (i, o, o) -> Nedeterminist
% alte modele: (i, i, i), (i, i, o), (i, o, i), (o, i, i)
%
% model matematic:
% candidat(l1..ln) =
%   1. (l1, l2..ln), daca n >= 2
%   2. (e, l1 (+) rez), daca n >= 2, unde (e, rez) = candidat(l2..ln)

candidat([H|T], H, T).

candidat([H|T], E, [H|R]):-
    candidat(T, E, R).


% Functia construieste restul permutarii, primind un prim element
% perm(L:list, U:int, R:list)
% L - lista de numere disponibile
% U - ultimul numar adaugat in permutare
% R - permutarea rezultata
% model de flux: (i, i, o) -> Nedeterminist
% alte modele: (i, i, i)
%
% model matematic:
% perm(l, u) =
%   1. [], daca l = []
%   2. e (+) perm(rez, e), daca |u - e| <= 2
%                        , unde (e, rez) = candidat(l)
perm([], _, []).

perm(L, U, [E|R]):-
    candidat(L, E, RestList),

    D is abs(U - E),
    D =< 2,

    perm(RestList, E, R).


% Functia creeaza o permutare a unei liste dupa conditiile dorite
% perm_init(L:list, R:list)
% L - lista de numere pe care o permutam
% R - permutarea rezultata
% model de flux: (i, o) -> Nedeterminist
% alte modele: (i, i)
%
% model matematic:
% perm_init(l) = perm(rez, e), unde (e, rez) = candidat(l)
%
perm_init(L, [E|R]):-
    candidat(L, E, RestList),
    perm(RestList, E, R).


% Functia returneaza toate permutarile cu nr de la N la 2 * N -  1
% perm_n(N:int, R:list)
% N - numarul dupa care permutam
% R - lista de permutari rezultata
% model de flux: (i, o) -> Determinist
% alte modele: (i, i)
%
% model matematic:
% perm_n(n) = U { P | P apartine perm_init(generam_list(n, n)) }
%
perm_n(N, R):-
    generam_lista(N, N, NList),
    findall(Rez, perm_init(NList, Rez), R).
