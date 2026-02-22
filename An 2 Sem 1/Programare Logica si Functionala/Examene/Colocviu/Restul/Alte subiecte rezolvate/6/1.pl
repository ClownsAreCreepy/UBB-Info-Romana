%f([], 0).
%f([H|T], P):-
%    !,
%    H mod 2 =:= 2,
%    f(T, P1),
%    P is P1 * H.
%f([_|T], P):-
%    f(T, P1),
%    P is P1.

% f([1, 2, 3, 4, 5, 6, 7, 8], P)
% In urma apelului, f va returna false. Datorita taieturii din a doua
% clauza, ea nu va mai intra in clauza 3, si va iesi cand verifica 1 si
% gata.
%
% F pentru a calcula numarul valorilor impare din lista:

f([], 0).

f([H|T], P):-
    H mod 2 =\= 0, !,
    f(T, P1),
    P is P1 + 1.

f([_|T], P):-
    f(T, P1),
    P is P1.






