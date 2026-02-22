% Functia returneaza un element dintr-o lista si lista fara acel element
% candidat(L:list, E:int, R:list)
% model de flux : (i, o, o) -> Nedeterminist
% alte modele:(i, i, o), (i, i, i), (i, o, i), (o, i, i)
% L - lista de unde extragem E - elementul extras R -
% lista fara elementul extras
%
% model matematic:
% candidat(l1..ln) =
%   1. (l1, l2..ln), daca n >= 1
%   2. (e, l1 (+) rez), daca n >= 1, unde (e, rez) = candidat(l2..ln)
candidat([H|T], H, T).

candidat([H|T], E, [H|R]):-
    candidat(T, E, R).


% Functia creaza un aranjament de K elemente cu suma S
% aranj(L:list, K:int, S:int, R:list)
% model de flux: (i, i, i, o) -> Nedeterminist
% alte modele: (i, i, i, i)
% L - lista de unde facem aranjamentul
% K - cate elemente mai trebuie adaugate in aranjament
% S - suma care mai trebuie atinsa prin adaugari
% R - aranjamentul curent
%
% model matematic:
% aranjament(l, k, e) =
%   1. [], daca s = 0 si k = 0
%   2. e (+) aranjament(rez, k - 1, s - e), daca k > 0
%                      , unde (e, rez) = candidat(l)
aranjament(_, 0, 0, []).

aranjament(L, K, S, [E|RestAranj]):-
    K > 0,
    candidat(L, E, RestList),
    % S >= E nu putem din cauza numerelor negative

    NewK is K - 1,
    NewS is S - E,

    aranjament(RestList, NewK, NewS, RestAranj).


% Functia returneaza toate aranjamentele de K elemente cu suma S
% aranj_suma(L:list, K:int, S:int, R:list)
% model de flux: (i, i, i, o) -> Determinist
% alte modele: (i, i, i, i)
% L - lista de unde facem aranjamentele
% K - marimea aranjamentelor
% S - suma elementelor aranjamentelor
% R - toate astfel de aranjamente posibile
%
% model matematic:
% aranj_sum(l, k, s) = U { A | A apartine aranjament(l, k, s) }
aranj_sum(L, K, S, R):-
    findall(Rez, aranjament(L, K, S, Rez), R).





