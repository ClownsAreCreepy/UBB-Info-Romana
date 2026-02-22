%f([], 0).

%f([H|T], S):-
%    !,
%    H mod 2 =:= 0,
%    f(T, S1),
%    S is S1 * H.

%f([_|T], S):-
%    f(T, S1),
%    S is S1.

% f([1, 2, 3, 4, 5], S)
% Taietura de la inceput face imposibila ajungerea la a treia clauza,
% asa ca apelul va verifica daca primul nr e par, 1 nu e par, deci va
% iesi fara sa mai faca altceva si va afisa doar un fals
%
% Reproiectare pentru a returna numarul de numere pare

f([], 0).

f([H|T], S):-
    f(T, S1),
    process(H, S1, S).

process(H, S1, S):-
    H mod 2 =:= 0, !,
    S is S1 + 1.

process(_, S, S).
