% freq(L: Lista de TElem, E: TElem, R: Intreg)
% model de flux: freq(i, i, o)
% L - lista de elemente unde ne uitam
% E - elementul dupa care ne uitam
% R - frecventa elementului in lista

freq([], _, 0):- !.

freq([E|T], E, R):-
    freq(T, E, R1),
    R is R1 + 1,
    !.

freq([_|T], E, R):-
    freq(T, E, R).


% elim_helper(L: Lista de TElem, O: Lista de TElem R: Lista de TElem)
% model de flux: elim_helper(i, i, o)
% L - lista initiala cu elemente
% O - lista originala, nemodificata
% R - lista rezultata fara elementele care se repeta

elim_helper([], _, []):- !.

elim_helper([H|T], L,  R):-
    freq(L, H, F),
    F > 1,
    elim_helper(T, L, R),
    !.

elim_helper([H|T], L, [H|R]):-
    elim_helper(T, L, R).


% elim(L: Lista de TElem, R: Lista de TElem)
% model de flux: elim(i, o)
% L - lista initiala cu elemente
% R - lista rezultata fara elemente care se repeta
elim(L, R):-
    elim_helper(L, L, R).



% max_elem(L: Lista de Intreg, R: Intreg)
% model de flux: max_elem(i, o)
% L - lista cu elemente unde ne uitam
% R - maximul din lista

max_elem([], 0):- !.

max_elem([H|T], H):-
    max_elem(T, M),
    M < H,
    !.

max_elem([_|T], M):-
    max_elem(T, M).

% elim_max_helper(L: Lista de Intreg, M: Intreg R: Lista de Intreg)
% model de flux: elim_max(i, i, o)
% L - lista initiala cu elemente
% M - elementul maxim al listei
% R - lista rezultata fara elementul maxim

elim_max_helper([], _, []):- !.

elim_max_helper([M|T], M, R):-
    elim_max_helper(T, M, R),
    !.

elim_max_helper([H|T], M, [H|R]):-
    elim_max_helper(T, M, R).


% elim_max(L: Lista de Intreg, R: Lista de Intreg)
% model de flux: elim_max(i, o)
% L - lista initiala cu elemente
% R - lista rezultata fara elementul maxim

elim_max(L, R):-
    max_elem(L, M),
    elim_max_helper(L, M, R).


