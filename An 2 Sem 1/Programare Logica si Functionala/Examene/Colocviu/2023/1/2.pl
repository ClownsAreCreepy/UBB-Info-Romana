% Functie care alege un element si returneaza resul listei
% candidat(L:integer*, E:integer, R:integer*)
% model de flux: (i, o, o) - Nedeterminist
% L - lista elementelor de unde alegem
% E - elementul pe care il extragem
% R - lista rezultata, fara elementul extras
%
% model matematic:
% candidat(l1..ln) =
%    1. (l1, l2..ln)
%    2. (e, l1 (+) res), unde (e, res) apartine candidat(l2..ln)
candidat([E|T], E, T).

candidat([H|T], E, [H|R]):-
    candidat(T, E, R).


% Genereaza o submultime de lungime K cu produsul elementelor P
% aranjamente(L:integer*, K:integer, P:integer, Rez:integer*)
% model de flux: (i, i, i, o) -> Nedeterminist
% L - lista de unde extragem elementele
% K - numarul de elemente ramase de ales
% P - produsul pe care trebuie sa il formam cu elementele ramase
% Rez - lista rezultat (submultimea generata)
%
% model matematic:
% aranjamente(L, K, P) =
%    1. [], daca K = 0 si P = 1 (Succes)
%    2. E (+) aranjamente(Rest, K - 1, P / E)
%                        , daca K > 0 si P % E = 0
%                        , unde (L, Rest) = candidat(L)
aranjamente(_, 0, 1, []):- !.

aranjamente(L, K, P, [E|RestSol]):-
    K > 0,
    candidat(L, E, Remainder),

    E =\= 0, % evitam impartirea la 0
    P mod E =:= 0, % verificam divizibilitatea

    NewK is K - 1,   % Apelam cu noi constrangeri
    NewP is P div E,

    aranjamente(Remainder, NewK, NewP, RestSol).


% Functia principala
% subm_produs(L:integer*, K:integer, P:integer, R:integer*)
% model de flux: (i, i, i, o) -> Determinist
% L - lista initiala
% K - dimensiunea sublistelor
% P - produsul tinta
% R - lista tuturor submultimilor valide
%
% model matematic:
% subm_produs = U { S | S apartine aranjamente(L, K, P) }
subm_produs(L, K, P, R):-
    findall(Rez, aranjamente(L, K, P, Rez), R).


