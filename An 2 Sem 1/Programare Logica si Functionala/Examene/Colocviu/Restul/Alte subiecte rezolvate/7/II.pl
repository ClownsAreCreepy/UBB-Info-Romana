% Functie care returneaza un element dintr-o lista si lista fara element
% candidat(L:list, E:int, R:list)
% L - lista de unde extragem
% E - elementul extras
% R - lista fara elementul extras
% model de flux: (i, o, o) -> Nedeterminist
% alte modele: (i, i, i), (i, i, o), (i, o, i), (o, i, i)
%
% model matematic:
% candidat(l1..ln) =
%   1. (l1, l2..ln), daca n >= 1
%   2. (e, l1 (+) rez), daca n >= 1, unde (e, rez) = candidat(l2..ln)
candidat([H|T], H, T).

candidat([H|T], E, [H|R]):-
    candidat(T, E, R).


% Functie care continua crearea unei permutari cu conditia ceruta
% perm(L:list, U:int, R:list)
% L - lista pe care o permutam
% U - ultimul element adaugat in permutare
% R - permutarea curenta
% model de flux: (i, i, o) -> Nedeterminist
% alte modele: (i, i, i)
%
% model matematic:
% perm(l1..ln, u) =
%   1. [], daca n = 0
%   2. e (+) perm(rez, e), daca |u - e|<=3,
%                       unde (e, rez) = candidat(l1..ln)
perm([], _, []).

perm(L, U, [E|R]):-
    candidat(L, E, RestList),

    D is abs(U - E),
    D =< 3,

    perm(RestList, E, R).


% Functie care incepe crearea unei permutari cu conditia ceruta
% perm_init(L:list, R:list)
% L - lista pe care o permutam
% R - permutarea curenta
% model de flux: (i, o) -> Nedeterminist
% alte modele: (i, i)
% 
% model matematic:
% perm_init(l) = e (+) perm(rez, e), unde (e, rez) = candidat(l)
perm_init(L, [E|R]):-
    candidat(L, E, RestList),
    perm(RestList, E, R).


% Functia returneaza toate permutarile cu conditia ceruta
% perm_dif(L:list, R:list)
% L - lista pe care o permutam
% R - lista tuturor permutarilor cerute
% model de flux: (i, o) -> Nedeterminist
% alte modele: (i, i)
% 
% model matematic:
% perm_dif(l) = U { P | P apartine perm_init(l) }
perm_dif(L, R):-
    findall(Rez, perm_init(L, Rez), R).
