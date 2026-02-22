from scipy.stats import norm
from matplotlib.pyplot import plot, show, grid
from numpy import linspace, mean, var
from random import randint

# Prepare variables
nr_simulations = 10000

fav_a = 0
fav_b = 0
Sm = []

# Prepare the grades
for _ in range(nr_simulations):
    M = randint(1, 10) + 10

    N = norm.rvs(60, 10, size = M)

    # a)
    if min(N) > 40:
        fav_a += 1

    # b)
    if max(N) < 75:
        fav_b += 1

    # c)
    Sm.append(sum(N))

# a)
print("P(min(N) > 40) =", fav_a / nr_simulations)

# b)
print("P(max(N) < 75) =", fav_b / nr_simulations)

# c)
print("E(Sm) =", mean(Sm))
print("V(Sm) =", var(Sm))

# d)
# M = 18

fav_d = 0

# Prepare grades
for _ in range(nr_simulations):
    N18 = norm.rvs(60, 10, size = 18) # M = 18

    if min(N18) > 50:
        fav_d += 1

print("P(min(N18) > 50) =", fav_d / nr_simulations)

# e)
x = linspace(20, 100, num = nr_simulations)
plot(x, norm.pdf(x, loc = 60, scale = 10))

grid()
show()