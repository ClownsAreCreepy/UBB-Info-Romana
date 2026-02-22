% Functia extrage un element din lista si intoarce elementul si lista
% candidat(L:list, E:integer, R:list)
% model de flux: (i, o, o) -> Nedeterminist
% L - lista de unde extragem
% E - elementul pe care il extragem
% R - lista rezultata, fara elementul extras
%
% model matematic:
% candidat(l1..ln) =
%    1. (l1, l2..ln),
%    2. (e, l1 (+) rez), unde (e, rez) = candidat(l1..ln)

candidat([E|T], E, T).

candidat([H|T], E, [H|R]):-
    candidat(T, E, R).

% Functia creaza un aranjament de K elemente cu produsul P
% aranj(L:list, K:integer, P:integer, R:list)
% model de flux: (i, i, i, o) -> Nedeterminist
% L - lista din care luam aranjamentul
% K - cate elemente mai trebuie bagate in aranjament
% P - produsul elementelor din aranjament
% R - aranjamentul curent
%
% model matematic
% aranj(l1..ln, K, P) =
%    1. [], daca K = 0 si P = 1 (Success)
%    2. e U aranj(RestL, K - 1, P \ E), daca K > 0 si |P| > E
%                      , unde (e, RestL) apartine candidat(l1..ln)
%    3. aranj(l2..ln, K, P), altfel

aranj(_, 0, 1, []):-!.

aranj(L, K, P, [E|RestSol]):-
    K > 0,
    candidat(L, E, RestL),
    P mod E =:= 0,
    NewK is K - 1,
    NewP is P div E,
    aranj(RestL, NewK, NewP, RestSol).

% Functia returneaza toate aranjamele de K elemete au produsul P
% aranj_produs(L:list, K:integer, P:integer, R:list)
% model de flux: (i, i, i, o) -> Determinist
% L - lista din care luam aranjamentele
% K - dimensiunea aranjamentelor
% P - produsul elementelor aranjamentelor
% R - lista de aranjamente rezultata
%
% model matematic
% aranj_produs(L, K, P) =
%    U { A | A apartine aranj(L, K, P) }

aranj_produs(L, K, P, R):-
    findall(Rez, aranj(L, K, P, Rez), R).

