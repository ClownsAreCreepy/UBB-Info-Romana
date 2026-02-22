% Functia returneaza un element dintr-o lista si lista dupa element
% candidat(L:list, E:int, R:list)
% L - lista de unde extragem
% E - elementul extras
% R - elementele dupa elementul extras
% model de flux: (i, o, o) -> Nedeterminist
% alte modele: (i, i, i), (i, i, o), (i, o, i), (o, i, i)
%
% model matematic:
% candidat(l1..ln) =
%   1. (l1, l2..ln), daca n >= 2
%   2. (e, rez), daca n >= 2, unde (e, rez) = candidat(l2..ln)
candidat([H|T], H, T).

candidat([_|T], E, R):-
    candidat(T, E, R).


% Functia construieste restul submultimii
% submultime(L:list, K:int, U:int, Ratie:int, R:list)
% L - lista de numere disponibile
% K - cate numere mai incap in submultime
% U - ultimul numar adaugat in submultime
% Ratie - ratia progresiei aritmetice actuale
% R - submultimea rezultata
% model de flux: (i, i, i, i o) -> Nedeterminist
% alte modele: (i, i, i, i, i)
%
% model matematic:
% submultime(l, k, u, ratie) =
%   1. [], daca k = 0
%   2. e (+) submultime(rez, k - 1, e, ratie)
%                        , daca k > 0 si e = u + ratie
%                        , unde (e, rez) = candidat(l)
submultime(_, 0, _, _, []).

submultime(L, K, U, Ratie, [E|R]):-
    K > 0,
    candidat(L, E, RestList),

    E =:= U + Ratie,

    NewK is K - 1,
    submultime(RestList, NewK, E, Ratie, R).


% Functia creaza o sublista a carei elemente sunt in p.a.
% submultime_init(L:list, K:int, R:list)
% L - lista de numere din care scoatem submultimea
% K - marimea submultimii
% R - submultimea rezultata
% model de flux: (i, i, o) -> Nedeterminist
% alte modele: (i, i, i)
%
% model matematic:
% submultimea_init(l, k) =
%   1. e1 (+) e2 (+) submultime(rez2, k - 2, e2,  ratie)
%                  , daca k >= 2
%                  , unde (e1, rez1) = candidat(l)
%                         (e2, rez2) = candidat(rez1)
%                         ratie = e2 - e1
%   2. (e), daca k = 1, unde (e, rez) = candidat(l)
%   3. (), daca k = 0
submultime_init(L, K, [E1, E2|R]):-
    K >= 2, !,
    candidat(L, E1, R1),
    candidat(R1, E2, R2),

    Ratie is E2 - E1,
    NewK is K - 2,

    submultime(R2, NewK, E2, Ratie, R).

submultime_init(L, 1, [E1]):-
    candidat(L, E1, _).

submultime_init(_, 0, []).


% Functia returneaza toate submultimile de K elemente in p. a.
% subm_prog(L:list, K:int, R:list)
% model de flux: (i, i, o) -> Determinist
% alte modele: (i, i, i)
% L - lista de unde facem submultimile
% K - marimea submultimilor
% R - toate astfel de submultimile posibile
%
% model matematic:
% subm_prog(l, k) = U { S | S apartine submultime_init(l, k) }
subm_prog(L, K, R):-
    findall(Rez, submultime_init(L, K, Rez), R).
