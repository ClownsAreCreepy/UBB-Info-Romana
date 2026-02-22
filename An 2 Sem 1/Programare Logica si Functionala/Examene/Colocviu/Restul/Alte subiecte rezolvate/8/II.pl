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


% Functie care creaza un aranjament de K elemente cu produs P
% aranj(L:list, K:int, P:int, R:list)
% L - lista de unde extragem
% K - numarul de elemente care mai incap in aranjament
% P - produsul la care trebuie sa ajungem
% R - aranjamentul curent
% model de flux: (i, i, i, o) -> Nedeterminist
% alte modele: (i, i, i, i)
%
% model matematic:
% aranj(l, k, p) =
%   1. [], daca k = 0 si p = 1
%   2. e (+) aranj(rez, k - 1, p / e), unde (e, rez) = candidat(l)
aranj(_, 0, 1, []).

aranj(L, K, P, [E|R]):-
    K > 0,
    candidat(L, E, RestList),

    P mod E =:= 0,

    NewK is K - 1,
    NewP is P div E,

    aranj(RestList, NewK, NewP, R).


% Functie care returneaza toate aranjamentele de K elemente cu produs P
% aranj_produs(L:list, K:int, P:int, R:list)
% L - lista de unde extragem
% K - marimea aranjamentelor
% P - produsul elementelor
% R - lista cu aranjamentele posibile
% model de flux: (i, i, i, o) -> Determinist
% alte modele: (i, i, i, i)
%
% model matematic:
% aranj_produs(l, k, p) = U { A | A apartine aranj(l, k, p) }
aranj_produs(L, K, P, R):-
    findall(Rez, aranj(L, K, P, Rez), R).



