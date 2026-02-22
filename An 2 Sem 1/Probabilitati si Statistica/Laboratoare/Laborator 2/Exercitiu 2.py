from math import dist
from matplotlib.pyplot import axis, plot, show
from random import random

def puncte_patrat(nr_puncte, cerinta):
    axis('square')
    axis((0,1,0,1))

    A = [0,0]
    B = [1,0]
    C = [1,1]
    D = [0,1]
    E = [0.5,0.5]

    match cerinta:
        case 1:
            count = 0

            for i in range(nr_puncte):
                P = [random(),random()]

                if (dist(E,P) < 0.5):
                    count += 1
                    plot(P[0], P[1], 'r*')
                else:
                    plot(P[0], P[1], 'b*')

            return count / nr_puncte

        case 2:
            count = 0

            for i in range(nr_puncte):
                P = [random(),random()]

                if dist(E, P) < min(dist(A, P), dist(B, P), dist(C, P), dist(D, P)):
                    count += 1
                    plot(P[0], P[1], 'r*')
                else:
                    plot(P[0], P[1], 'b*')

            return count / nr_puncte

        case 3:
            count = 0

            for i in range(nr_puncte):
                P = [random(),random()]

                triunghi = (dist(D, P) * dist(D, P) + dist(A, P) * dist(A, P) < 1) + (dist(B, P) * dist(B, P) + dist(A, P) * dist(A, P) < 1) + (dist(D, P) * dist(D, P) + dist(C, P) * dist(C, P) < 1) + (dist(C, P) * dist(C, P) + dist(B, P) * dist(B, P) < 1)

                if triunghi == 2:
                    count += 1
                    plot(P[0], P[1], 'r*')
                else:
                    plot(P[0], P[1], 'b*')

            return count / nr_puncte

def frecvente_geometrice():
    arie_partat = 1
    arie_cerc = 3.14 * 0.25

    print("Frecventa 1")
    print(arie_cerc / arie_partat)

    arie_romb = 0.5
    print("Frecventa 2")
    print(arie_romb / arie_partat)

    arie_x = 3.14 / 2 - 1
    print("Frecventa 2")
    print(arie_x / arie_partat)

n = int(input("Nr puncte= "))
c = int(input("Cerinta= "))
print(puncte_patrat(n, c))
print(frecvente_geometrice())
show()