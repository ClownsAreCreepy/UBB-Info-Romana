% is_prime(N)
% model de flux: is_prime(i)
is_prime(N) :-
    N > 1,
    \+ has_divisor(N, 2).

% has_divisor(N, D)
% model de flux: has_divizor(i, i)
has_divisor(N, D) :-
    D * D =< N,
    (N mod D =:= 0 ; D1 is D + 1, has_divisor(N, D1)).


% a)
% dup_primes(List, Result)
% model de flux: dup_primes(i, o)
dup_primes([], []).
dup_primes([H|T], [H,H|R]) :-
    is_prime(H), !,
    dup_primes(T, R).
dup_primes([H|T], [H|R]) :-
    dup_primes(T, R).


% is_list(X)
% model de flux: is_list(i)
is_list([]).
is_list([_|T]) :-
        is_list(T).

% b)
% dup_primes_hetero(List, Result)
% model de flux: dup_primes_hetero(i, o)
dup_primes_sublist([], []).
dup_primes_sublist([H|T], [HR|R]) :-
    is_list(H), !,
    dup_primes(H, HR),           % apply part a inside sublists
    dup_primes_sublist(T, R).
dup_primes_sublist([H|T], [H|R]) :-
    dup_primes_sublist(T, R).





