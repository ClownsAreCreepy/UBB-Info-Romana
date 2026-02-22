% cmmdc(A: Intreg, B: Intreg, R: Intreg)
% model de flux: cmmdc(i, i, o)
% A - primul numar
% B - al doilea numar
% R - cel mai mare divizor comun

cmmdc(A, 0, A):- !.

cmmdc(A, B, R):-
    B =\= 0,
    Rest is A mod B,
    cmmdc(B, Rest, R).


% cmmdcList(L: Lista de Intreg, R: Intreg)
% model de flux: cmmdcList(i, o)
% L - lista de unde facem calculele
% R - cmmdc-ul elementelor din lista

cmmdcList([], _):- !.

cmmdcList([H|T], R1):-
    cmmdcList(T, R),
    cmmdc(H, R, R1).


% powerOfTwo(A: Intreg)
% model de flux: powerOfTwo(i)
% A - numarul pe care il verificam daca e putere de 2

powerOfTwo(1):- !.

powerOfTwo(-1):- !.



powerOfTwo(A):-
    A mod 2 =:= 0,
    B is A div 2,
    powerOfTwo(B).


% add(L: Lista de Intreg, V: Intreg, R: Lista de Intreg)
% model de flux: add(i, i, o)
% L - lista pe care iteram
% V - valoarea pe care o adaugam
% R - lista rezultata dupa adaugari

add([], _, []):- !.

add([H|T], V, [H, V|R]):-
    powerOfTwo(H),
    add(T, V, R),
    !.

add([H|T], V, [H|R]):-
    add(T, V, R).
