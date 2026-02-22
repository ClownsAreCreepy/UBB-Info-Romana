from random import randint
from matplotlib.pyplot import plot, grid, title, show

def estimate(n, nr_sims):
    count = 0
    for i in range(nr_sims):
        birthdays = []
        for j in range(n):
            birthdays.append(randint(1, 365))
        birthdays = set(birthdays)
        if len(birthdays) < n:
            count += 1

    return count/nr_sims

def same_birthday(n):
    if n > 365:
        return 1

    produs = 1
    for i in range(n):
        produs *= (365 - i + 1) / 365

    return 1-produs

n=int(input("n= "))
print("Prin simulari: ")
print(estimate(n, 1000))
print("Prin calcul: ")
print(same_birthday(n))

title('Simulari')
xs = range(2,50)
ys = [estimate(x, 1000) for x in xs]
plot(xs, ys, 'r*')
grid()
show()

title('Calcul')
xs = range(2,50)
ys = [same_birthday(x) for x in xs]
plot(xs, ys, 'r*')
grid()
show()