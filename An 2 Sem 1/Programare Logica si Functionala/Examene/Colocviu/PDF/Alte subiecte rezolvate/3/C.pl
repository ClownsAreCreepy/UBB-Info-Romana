% Daca o suma de numere este impara, atunci numarul de factori impari
% din acea suma este INTOTDEAUNA impar, deci nu tre sa ne complicam cu
% countImpar

% subm_aux(L:list, Sum:int, R:list)
% model de flux: (i, i, i, o) -> Nedeterminist
% model matematic:
% subm_aux(l1..ln, sum) =
% 1. [], daca n = 0 si sum % 2 = 1 (Validatre finala)
% 2. l1 U subm_aux(rest, sum + l1) (Alegem l1)
% 3. subm_aux(rest, sum) (Sarim peste l1)

subm_aux([], Sum, []):-
    Sum mod 2 =:= 1.

subm_aux([H|T], Sum, [H|Rest]):-
    NewSum is Sum + H,
    subm_aux(T, NewSum, Rest).

subm_aux([_|T], Sum, Rest):-
    subm_aux(T, Sum, Rest).


% subm_sumaImpara(L:list, R:list)
% model de flux: (i, o) -> Determinist
% model matematic:
% subm_sumaImpara(L) = U { S | S apartine subm_aux(L, 0) }

submultimi(L, R):-
    findall(Rez, subm_aux(L, 0, Rez), R).
