f([], _, 0).

f([H|T], V, P):-
    !,
    H > V,
    f(T, V, P1),
    P = P1 * V.

f([_|T], V, P):-
    f(T, V, P).

% f([2, 5, 6, 9, 7, 6, 9], 4, P)

% Datorita taieturii, f nu ajunge niciodata in clauza 3
% La prima verificare, se va face 2 > 4, va fi fals
% Astfel, va iesi din executie si returneaza false rosu si atat
