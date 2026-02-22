f(50, 1):-!.
f(I, Y):-
    J is I + 1,
    f(J, S),
    process(I, S, Y).

process(I, S, Y):-
    S < 1, !,
    K is I - 2,
    Y is K.

process(_, S, S).
