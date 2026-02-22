% P20
% Det poz elem maxim intr-o lista liniara

% ex: [10,14,12,13,14] -> [2,5]

% detMax(L) = {
%                   L[1], L[1] > detMax(L[2:])
%                   detMax(L[2:]), altfel
% }

% detMax(L:list, E:integer)
% detMax(i, o), detMax(i, i)
% L: list
% E: integer

detMax([], 0).
detMax([H|T], E) :- 
    detMax(T, E1), 
    H > E1, 
    E is H,!.
detMax([_|T], E) :- 
    detMax(T, E).


% detPozMaxW(Lista) = {
%                 detPozMax(Lista, 1, detMax(Lista)).          
% }
% detPozMaxW(L:List, R:list)
% (i,o),(i,i)
detPozMaxW(L,R):-
    detMax(L, E),
    detPozMax(L,1,E,R).

% detPozMax(L,Poz,E) = {
%           [], L=[]
%           L[1] U detPozMax(L[2:], Poz+1, E), L[1] = E
%           detPozMax(L[2:],Poz+1,E), altfel
% }
% detPozMax(L:list, Poz:integer, E:integer, R:list)
% L - list
% Poz - integer
% E - integer
% R - list
% detPozMax(i,i,i,o),(i,i,i,i)
detPozMax([],_,_,[]).
detPozMax([H|T],Poz,E,[Poz|R]):-
    H = E,!,
    Poz1 is Poz+1,
    detPozMax(T,Poz1,E,R).

detPozMax([_|T],Poz,E,R):-
    Poz1 is Poz+1,
    detPozMax(T,Poz1,E,R).