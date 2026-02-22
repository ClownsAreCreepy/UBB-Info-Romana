% Functia returneaza un element si lista dupa acel element
% candidat(L:list, E:pair(int, int), R:list)
% L - lista de unde extragem
% E - elementul pe care il extragem
% R - elementele dupa elementul extras
% model de flux: (i, o, o) -> Nedeterminist
% alte modele: (i, i, i), (i, o, i), (i, i, o), (o, i, i)
%
% model matematic:
% candidat(l1..ln) =
%   1. (l1, l2..ln), daca n >= 1     (Select)
%   2. candidat(l2..ln), daca n >= 1 (Skip)
candidat([H|T], H, T).

candidat([_|T], E, R):-
    candidat(T, E, R).


% Functia verifica daca 3 puncte sunt coliniare
% verif_coliniar(P1:pair(int, int), P2:pair(int, int), P3:pair(int, int)
% P1, P2, P3 - punctele pe care le verificam
% model de flux: (i, i, i) -> Determinist
% alte modele: nu sunt
%
% model matematic:
% verif_coliniar((X1, Y1), (X2, Y2), (X3, Y3)) =
%    1. true, daca (Y2 - Y1) * (X3 -X2) = (Y3 -Y2) * (X2 - X1)
%    2. false, altfel
verif_coliniar((X1, Y1), (X2, Y2), (X3, Y3)):-
    CO1 is Y2 - Y1,
    CO2 is X3 - X2,
    CO3 is Y3 - Y2,
    CO4 is X2 - X1,
    CO1 * CO2 =:= CO3 * CO4.


% Functia incearca sa ia puncte pe aceeasi linie cu 2 alese deja
% Orice 2 puncte sunt coliniare
% 3 sau mai multe puncte sunt coliniare
% daca respecta formula: (y2 - y1) * (x3 - x2) = (y3 - y2) * (x2 - x1)
% construieste(L:list, P1:pair, P2:pair, Rez:list)
% L - lista de unde extragem
% P1, P2 - punctele care definesc linia curenta
% R - submultimea curenta
% model de flux: (i, i, i, o) -> Nedeterminist
% alte modele: (i, i, i, i)
%
% model matematic:
% construieste(l, p1, p2) =
%   1. [], (ne oprim oricand)
%   2. e (+) construieste(rez, p1, p2), daca verif_coliniar(p1, p2, e)
%                            , unde (e, rez) = candidat(l)
construieste(_, _, _, []).

construieste(L, P1, P2, [P3|Rest]):-
    candidat(L, P3, Remaining),
    verif_coliniar(P1, P2, P3),
    construieste(Remaining, P1, P2, Rest).


% Functia creaza o submultime de puncte coliniare
% submultime(L:list, R:list)
% L - lista de unde alegem
% R - submultimea curenta
% model de flux: (i, o) -> Nedeterminist
% alte modele: (i, i)
%
% model matematic:
% submultime(l) = p1 (+) p2 (+) construieste(R2, p1, p2)
%               , unde (p1, R1) = candidat(l)
%                      (p2, R2) = candidat(R1)
submultime(L, [P1, P2 |Rest]):-
    candidat(L, P1, R1),
    candidat(R1, P2, R2),
    construieste(R2, P1, P2, Rest).


% Functia returneaza toate submultimile de puncte coliniare
% subm_col(L:list, R:list)
% L - lista de unde alegem
% R - lista cu toate submultimile gasite
% model de flux: (i, o) -> Determinist
% alte modele: (i, i)
%
% model matematic:
% subm_col(l) = U { S | S apartine submultime(l) }
subm_col(L, R):-
    findall(S, submultime(L, S), R).

