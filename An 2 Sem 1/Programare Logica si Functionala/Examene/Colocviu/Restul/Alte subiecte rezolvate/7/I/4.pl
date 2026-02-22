f([], []).

f([H|T], [H|S]):-
    f(T, S).  % clauza tine in lista

f([H|T], S):-
    H mod 2 =:= 0,
    f(T, S).  % clauza elimina din lista

% deci se elimina numerele pare

% [1, 2, 3]
% [1, 3]
% false
