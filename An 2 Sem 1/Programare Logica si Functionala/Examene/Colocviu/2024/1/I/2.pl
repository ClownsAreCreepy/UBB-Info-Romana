f([], []).

f([H|T], [H|Rez]):-
    H > 0,
    f(T, Rez),
    !.

f([_|T], Rez):-
    f(T, Rez).


% Elimina valorile negative:
% f([2, -1, 3, -2, 7], Rez)
% -> [2, 3, 7]
