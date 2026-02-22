from matplotlib.pyplot import show, hist, grid, xticks, plot
from scipy.stats import expon,uniform
from math import log

def dist(alpha, N):

    X = []
    U = uniform.rvs(size=N)

    for u in U:
        val = -(1/alpha) * log(1 - u)
        X.append(val)

    return X

def histo(N):
    alpha = 1/12

    data = dist(alpha, N)

    hist(data, bins = 12, density = True, range = (0,61))

    x = range(60)
    plot(x, expon.pdf(x, loc=0, scale=10), 'r-')

    xticks(range(0, 60, 5))
    grid()
    show()


def estimate(N):
    alpha = 1/12
    data = dist(alpha, N)

    nr = 0
    for x in data:
        if x >= 5:
            nr += 1

    return nr / N

histo(1000)
print("Estimare: " + estimate(1000).__str__())

alpha = 1/12
prob = 1 - expon.cdf(5, loc = 0, scale = 1/alpha)
print("Teoretica: ", end='')
print(prob)