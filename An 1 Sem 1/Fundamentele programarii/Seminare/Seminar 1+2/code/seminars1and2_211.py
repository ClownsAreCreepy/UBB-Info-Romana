"""
Modificari fata de seminar:
    - adaugat F2 (adaugare la lista)
    - adaugat F3: gasire minim in doua moduri
        --functie built-in min() + metoda lista pentru gasirea indexului unui element dat (.index)
        --prin parcurgerea listei, exersat enumerate (https://realpython.com/python-enumerate/) si folosirea
           math.inf (https://docs.python.org/3/library/math.html#math.inf)
        --returnat valori multiple din functie (tuplu)
    - adaugat F4:
        --stergere din lista folosind .pop(index)
        --de ce nu am folosit for?
        --alte instructiuni de stergere din lista: .remove(valueDeSters)
    - de adaugat: F5: Verificare proprietate de multime, afisare frecventa valori
        --idee 1: folosire dictionar (cheie = numar, valoare = frecventa numarului)
        --idee 2: identificare elemente unice in lista (transofrmare in set?), folosire lista.count(value) pentru fiecare
        --...

    - redenumit variabile, metode (nume in limba engleza, for consistency - aveam si RO, si EN)
"""
import math


def print_menu():
    print("1. Citire lista")
    print("2. Adaugare la lista")
    print("3. Afisare informatii minim")
    print("4. Eliminare numere prime")
    print("P. Afisare lista curenta")
    print("E. Iesire")


def transform_to_int_list(s_lista: str) -> list:
    """
    Transforma un string dat intr-o lista de numere intregi
    :param s_lista: string sub forma '1 2 3 4 5'
    :return: lista corespunzatoare stringului dat
    """
    split_list = s_lista.split()
    # print("Lista dupa split', split_list)
    numbers_list = []
    for nr_str in split_list:
        numbers_list.append(int(nr_str))

    return numbers_list


def add_to_pos(lst: list, pos: int, elem: int):
    """
    Adauga elementul elem pe pozitia pos in lista lst
    :param lst: lista in care se adauga
    :param pos: pozitia pe care se adauga
    :param elem: elementul care se insereaza
    :return: None; lista data ca parametru este modificata prin inserarea elementului
             elem pe pozitia pos
    """
    lst.insert(pos, elem)


def find_min_info(numbers_list: list) -> tuple:
    """
    Gaseste cel mai mic numar si pozitia sa in lista
    :param numbers_list: lista in care se cauta minimum
    :return: un tuplu in care pe prima pozitie se afla minimul din lista,
                iar pe a doua indexul acestuia
    """
    min_number = min(numbers_list)
    min_index = numbers_list.index(min_number)
    # keep in mind: you can run help(list.index) or help(list) or help(str) etc
    # to get info on available methods for a type (e.g. help(list), help(dict), help(tuple)...)
    # or to get info on specific method (help(dict.update), help(list.remove),...)
    # either in a script or in IDLE, or in
    # Python Console in PyCharm (found in the tabs which are usually at the bottom of the screen)

    # Another way:
    # min_number = math.inf
    # min_index = -1
    # for index, number in enumerate(numbers_list):
    #     if number<min_number:
    #         min_number = number
    #         min_index = index
    return min_number, min_index


def is_prime(number: int) -> bool:
    """
    Verifica daca un numar dat ca parametru este prim
    :param number: numarul de verificat
    :return: True daca numarul este prim, fals altfel
    """
    if number < 2:
        return False
    if number == 2:
        return True
    if number % 2 == 0:
        return False
    for i in range(2, number // 2):
        if number % i == 0:
            return False
    return True


def remove_primes(numbers_list: list) -> None:
    """
    Elimina numerele prime din lista data
    :param numbers_list: lista din care se elimina numerele
    :return: None; lista data ca parametru se modifica prin eliminarea
             numerelor prime
    """
    i = 0
    while i < len(numbers_list):
        if is_prime(numbers_list[i]):
            numbers_list.pop(i)
        else:
            i += 1


def run():
    numbers_list = []
    while True:
        print_menu()
        option = input("Introduceti optiunea:")
        option = option.strip().upper()

        # also see: match...case
        if option == '1':
            list_as_str = input("Introudceti lista: ")
            numbers_list = transform_to_int_list(list_as_str)

        elif option == '2':
            # adaugare la lista
            nr_to_add = int(input("Numarul care se adauga:"))
            pos_to_add = int(input("Pozitia pe care se adauga:"))
            add_to_pos(numbers_list, pos_to_add, nr_to_add)

        elif option == '3':
            minimum, min_index = find_min_info(numbers_list)
            print("Mininum din lista este", minimum, "si se afla pe pozitia", min_index)

        elif option == '4':
            remove_primes(numbers_list)
        elif option == '5':
            pass
        elif option == 'P':
            print("Lista curenta:", numbers_list)
        elif option == 'E':
            print("Exiting...")
            break


run()
