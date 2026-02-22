from random import choice
from matplotlib.pyplot import hist, show, grid, xticks
from numpy import mean

# a)
# Prepare variables
nr_simulations = 1000

U1 = [1, 1, 2, 2, 2, 3, 3, 4]

Ys = []

# Loop for simulations
for _ in range(nr_simulations):
    # Add element to U2
    U2 = [1, 1, 2, 3, 4, choice(U1)]

    # Extract element from U2 and put it in the thing
    Y = choice(U2)
    Ys.append(Y)

print("1000 Y:", Ys)

# b)
# Make bins for values 1 through 4, centered
bins = [k + 0.5 for k in range (5)]

# Make and show the hist (no density, because we want absolute values
hist(Ys, bins, density = False, color = 'r', edgecolor = 'k')

# Make only the bins from 1 through 4 appear
xticks(range(1, 5))

grid()
show()

# c)
# Average value of Y
print("Average value of Y:", mean(Ys))