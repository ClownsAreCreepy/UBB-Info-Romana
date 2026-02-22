p(1).
p(2).

q(1).
q(2).

r(1).
r(2).

s:-!, p(X), q(Y), r(Z), write(X), write(Y), write(Z), nl.

% Taietura e la inceput, si s are o singura clauza, deci ! nu prea face
% nimic, deoarece nu opreste backtracking-ul pe ce e in fata, doar pe ce
% e in spate in aceeasi clauza.
%
% Deci p(X) va fi 1, q va fi 1, r va fi 1, deci 1 1 1, iar deoarece s
%a reusit, va printa true
% Apoi va veni backtracking si va modifica solutiile, astfel vor aparea
% toate aranjamentele de 3 a cifrelor 1 si 2, in ordinea asta:
% 1 1 1
% true
% 1 1 2
% true
% 1 2 1
% true
% 1 2 2
% true
% 2 1 1
% true
% 2 1 2
% true
% 2 2 1
% true
% 2 2 2
% true
