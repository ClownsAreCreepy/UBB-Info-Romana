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


% Functie care creaza un aranjament de K elemente cu suma S
% aranj(L:list, K:int, S:int, R:list)
% L - lista de unde extragem
% K - numarul de elemente care mai incap in aranjament
% S - suma la care trebuie sa ajungem
% R - aranjamentul curent
% model de flux: (i, i, i, o) -> Nedeterminist
% alte modele: (i, i, i, i)
%
% model matematic:
% aranj(l, k, s) =
%   1. [], daca k = 0 si s = 0
%   2. e (+) aranj(rez, k - 1, s - e), unde (e, rez) = candidat(l)
%                                    , daca k > 0
aranj(_, 0, 0,  []).

aranj(L, K, S, [E|R]):-
    K > 0,
    candidat(L, E, RestList),

    % S => E, nu putem spune asta deoarece E este intreg

    NewK is K - 1,
    NewS is S - E,

    aranj(RestList, NewK, NewS, R).


% Functie care returneaza toate aranjamentele de K elemente cu suma S
% aranj_suma(L:list, K:int, S:int, R:list)
% L - lista de unde extragem
% K - marimea aranjamentelor
% S - suma elementelor
% R - lista cu aranjamentele posibile
% model de flux: (i, i, i, o) -> Determinist
% alte modele: (i, i, i, i)
%
% model matematic:
% aranj_suma(l, k, s) = U { A | A apartine aranj(l, k, s) }
aranj_suma(L, K, S, R):-
    findall(Rez, aranj(L, K, S, Rez), R).
