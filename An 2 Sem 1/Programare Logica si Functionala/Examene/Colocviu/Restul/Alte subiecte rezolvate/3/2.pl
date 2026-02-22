% Functia returneaza un element dintr-o lista si lista fara el
% candidat(L:list, E:int, R:list)
% model de flux: (i, o, o) -> Nedeterminist
% L - lista de unde extragem
% E - elementul pe care il extragem
% R - lista fara elementul respectiv
%
% model matematic:
% candidat(l1..ln) = |(l1, l2..ln),
%                    |(e, l1 (+) rez), unde (e, rez) = candidat(l2..ln)
candidat([E|T], E, T).

candidat([H|T], E, [H|R]):-
    candidat(T, E, R).


% Functia creaza un aranjament de K elemente cu suma S
% aranj(L:list, K:int, S:int, R:list)
% model de flux: (i, i, i, o) -> Nedeterminist
% L - lista din care luam aranjamentul
% K - cate elemente mai trebuie bagate in aranjament
% S - suma elementelor din aranjament
% R - aranjamentul curent
%
% model matematic:
% aranj(L, k, s) = | [], daca k = 0 si s = 0
%                       | e (+) aranj(rez, k-1, s-e)
%                                    , daca  k > 0
%                                    , unde (e, rez) = candidat(L)
aranj(_, 0, 0, []).

aranj(L, K, S, [E|RestAranj]):-
    K > 0,
    candidat(L, E, RestList),
    % S >= E, nu punem asta pentru ca numere negative

    NewS is S - E,
    NewK is K - 1,
    aranj(RestList, NewK, NewS, RestAranj).


% Functia returneaza toate aranjamentele de K elemente cu suma S
% aranj_suma(L:list, K:int, S:int, R:list)
% model de flux: (i, i, i, o) -> Determinist
% L - lista din care luam aranjamentele
% K - dimensiunea aranjamentelor
% S - suma elementelor aranjamentelor
% R - lista de aranjamente generate
%
% model matematic:
% aranj_suma(L, K, S) = U { A | A apartine aranj(L, K, S) }
aranj_suma(L, K, S, R):-
    findall(Rez, aranj(L, K, S, Rez), R).
