w(N, N).

w(J, I):-
    I < 10,
    I1 is I + 1,
    w(J, I1).

r(K, J):-
    w(J, K),
    write(J),
    write(" "),
    fail.

% 6 7 8 9 10
% false
