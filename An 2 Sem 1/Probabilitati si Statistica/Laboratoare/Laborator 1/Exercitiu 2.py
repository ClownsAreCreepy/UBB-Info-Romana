from random import sample
from math import perm, comb
from itertools import permutations, combinations

def aranjamente(population, k, numar_total = False, aleator = False):
    if numar_total == False and aleator == False:
        print(list(permutations(population, k)))
    if numar_total == True:
        print(perm(len(population), k))
    if aleator == True:
        print(sample(population, k))

def combinari(population, k, numar_total = False, aleator = False):
    if numar_total == False and aleator == False:
        print(list(combinations(population, k)))
    if numar_total == True:
        print(comb(len(population), k))
    if aleator == True:
        print(sample(population, k))

aranjamente('word', 2)
aranjamente('word', 2, numar_total = True)
aranjamente('word', 2, aleator = True)
aranjamente('word', 2, numar_total = True, aleator = True)