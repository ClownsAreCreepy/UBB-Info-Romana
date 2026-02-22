f([], 0).

f([H|T], S):-
    f(T, S1),
    S1 is S - H.

f_fix([], 0).

f_fix([H|T], S):-
    f_fix(T, S1),
    S is S1 + H.
