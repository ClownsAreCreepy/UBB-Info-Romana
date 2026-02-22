f(100,1):-!.

f(K,X):-
    K1 is K + 1,
    f(K1, Y),  % singurul apel recursiv din tot programul
    process_result(K1, Y, X).

process_result(K1, Y, X):-
    Y > 1, !,
    K2 is K1 - 1,
    X is K2 + Y.

process_result(_, Y, X):-
    Y > 0.5, !,
    X is Y.

process_result(K1, Y, X):-
    X is Y - K1.
