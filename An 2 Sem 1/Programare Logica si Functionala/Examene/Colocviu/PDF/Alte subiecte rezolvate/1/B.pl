% Extrage E din lista, returnand restul listei
% candidat(L:integer*, E:integer, R:integer*)
% model de flux: candidat(i, o, o) -> Nondeterminist
% L - Lista de unde extragem elementul
% E - elementul pe care il extragem
% R - lista rezultata, fara elementul extras
%
% model matematic:
% candidat(l1..ln) =
%   1. (l1, l2..ln)
%   2. (E, l1 (+) res), daca candidat(l2..ln) = (E, res)

candidat([E|T], E, T).

candidat([H|T], E, [H|Rest]):-
    candidat(T, E, Rest).


% Verifica ca diferenta in modul intre X si Y sa fie <= 3
% check_diff(X:integer, Y:integer)
% model de flux: check_diff(i, i) -> Deterministic
% X - primul numar
% Y - al doilea numar
%
% model matematic:
% check_diff(X, Y) =
%   1. true, daca |X - Y| <= 3
%   2. false, altfel

check_diff(X, Y):-
    D is abs(X - Y),
    D =< 3.


% Alege primul element (care nu are constrangeri)
% permutare(L:integer*, P:integer*)
% model de flux: (i, o)
% L - lista pe care o permutam
% P - permutarea finala a listei
%
% model matematic:
% permutare(l1..ln) =
%    candidat(l1..ln)
%    perm_aux(Rest, H), unde (H, Rest) = candidat(l1..ln)
permutare(L, [H|T]):-
    candidat(L, H, Rest),
    perm_aux(Rest, H, T).

% Ia elementele urmatoare pentru permutare si verifica daca sunt valide
% perm_aux(L:integer*, LastVal:integer, R:integer*)
% model de flux: (i, i, o)
% L - lista de unde luam elementele pentru permutare
% LastVal - ultimul element adaugat din permutare
% Result - permutarea pe care am construit-o
%
% model matematic:
% perm_aux(l1..ln, LastVal) =
%    1. [], daca n = 0
%    2. E (+) perm_aux(RestList, E)
%               , daca check_diff(E, LastVal) = true
%               , unde (E, RestList) = candidat(l1..ln)
perm_aux([], _, []).

perm_aux(L, LastVal, [E|R]):-
    candidat(L, E, RestList),
    check_diff(E, LastVal),
    perm_aux(RestList, E, R).


% Functia principala, care gaseste toate permutarile valabile
% all_permutations(L, Result)
% model de flux: permutare(i, o) -> Deterministic
% L - lista data de utilizator, din care generam permutarile
% Result - lista formata din toate permutarile posibile
%
% model matematic:
% all_permutations(L, Result) = U {P | P apartine permutare(L)}

all_permutations(L, Result):-
    findall(P, permutare(L, P), Result).










