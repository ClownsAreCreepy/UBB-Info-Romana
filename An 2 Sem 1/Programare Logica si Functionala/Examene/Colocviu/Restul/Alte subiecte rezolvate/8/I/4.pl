f([], 0).

f([H|T], S):-
    f(T, S1),
    S1 is S - H.

% Va da eroare 'Arguments not sufficiently instantiated', deoarece S
% este variabila de output si este libera in momentul in care se face
% S1 is S - H
