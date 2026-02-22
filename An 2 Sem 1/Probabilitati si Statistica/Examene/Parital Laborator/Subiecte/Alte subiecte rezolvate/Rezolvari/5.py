from scipy.stats import uniform
from matplotlib.pyplot import show, grid, plot
from numpy import linspace, mean, var
from random import randint

nr_simulations = 10000

# a)
Y = []

# Create a number of Ym
for _ in range(nr_simulations):
    M = randint(1, 5) + 5

    X = uniform.rvs(loc = -1, scale = 2, size = M)

    Ym = 1

    for x in X:
        Ym *= x

    Y.append(Ym)

# Calculate the probability
favorable = sum(1 for y in Y if 0 < y < 0.1)

# fav cases / all cases
print("P(0 < Ym < 0.1) =", favorable / nr_simulations)


# b)
print ("E(Y) =", mean(Y))
print ("V(Y) =", var(Y))


# c)
# Fix M on 6
# Create another array of Y
Y6 = []

for _ in range(nr_simulations):
    X6 = uniform.rvs(loc = -1, scale = 2, size = 6) # M = 6

    Ym = 1
    for x in X6:
        Ym *= x

    Y6.append(Ym)

favorable_6 = sum(1 for y in Y6 if y > 0.1)

print("P(Ym > 0.1 | M = 6) =", favorable_6 / nr_simulations)


# d)
# P(| Ym | < 1) is legit 1
# Normally, we calculate this type of stuff like this
# P(| Ym | < 1) = P(-1 < Ym < 1) = F(1) - F(-1)

favorable_d = sum(1 for y in Y if -1 < y < 1)
print("P(| Ym | < 1) =", favorable_d / nr_simulations)

# e)
# Line
x = linspace(-2, 2, nr_simulations)
plot(x, uniform.pdf(x, loc = -1, scale = 2), 'r-')

# Points
plot([-1], [0], 'ko')
plot([1], [1], 'ko')

grid()
show()