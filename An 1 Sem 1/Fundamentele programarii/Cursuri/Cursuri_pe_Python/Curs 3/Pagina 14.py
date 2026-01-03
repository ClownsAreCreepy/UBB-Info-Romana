def patrat(a):
    return a*a


def modul(a):
    if a<0: return -a
    return a


#assign a function to a variable
func = patrat
#Mine:print(func(-2))
func = modul
#Mine:print(func(-2))


#list of functions
lstFct = [patrat,modul]
for fct in lstFct:
    pass
    #Mine:print(fct(-2))


def aplica(lista, fnc):
    """
    Aplica functia fnc pe fiecare element al listei
    lista - lista de elemente
    fnc - functie cu un singur parametru
    returneaza o lista noua
    """
    rez = []
    for el in lista:
        rez.append(fnc(el))
    return rez

#Mine:print(aplica([1,2,-3,5,-2], patrat))