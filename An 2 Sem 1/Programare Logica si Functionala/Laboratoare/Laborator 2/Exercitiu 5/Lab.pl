% del(L: Lista de TElem, E: TElem Atom, R: Lista de TElem)
% model de flux: del(i, i, o)
% L - lista de elemente initiale
% E - atomul pe care il vom sterge din lista
% R - lista rezultata de elemente

del([], _, []):- !.

del([E|T], E, R):-
    del(T, E, R),
    !.

del([H|T], E, [H|R]):-
    del(T, E, R).



% freq(L: Lista de TElem Atom, E: TElem, R: Intreg)
% model de flux: freq(i, i, o)
% L - lista de elemente in care ne uitam
% E - elementul pe care il numaram
% R - frecventa elementului din lista

freq([], _, 0):- !.

freq([E|T], E, R1):-
    freq(T, E, R),
    R1 is R + 1,
    !.

freq([_|T], E, R):-
    freq(T, E, R).


% pair(L: Lista de TElem Atom, R: Lista de perechi [Atom, freq])
% model de flux: pair(i, o)
% L - lista de elemente in care ne uitam
% R - lista de perechi [element, frecventa] care rezulta

pair([], []):- !.

pair([H|T], [[H|F]|RP]):-
    freq([H|T], H, F),
    del(T, H, T1),
    pair(T1, RP).
