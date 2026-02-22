% Caz baza 1: Lista e goala
scan_pass([], [], false):-!.

% Caz baza 2: Lista mai are un singur element
scan_pass([X], [X], false):-!.

% Caz A < B (modificam A)
scan_pass([A,B|T], [NewA|Rest], true):-
    A < B,
    NewA is A * 2,
    scan_pass([B|T], Rest, _),
    !.

% Caz A >= B (ramane A)
scan_pass([A|T], [A|Rest], Changed):-
    scan_pass(T, Rest, Changed).


% Wrapper care tot cheama scan_pass pana cand nu mai sunt schimbari
process(L, Result):-
    scan_pass(L, NewL, Changed),
    (   Changed = true ->
          process(NewL, Result)
        ; Result = L
    ).
