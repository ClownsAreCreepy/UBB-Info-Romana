from scipy.stats import uniform
from matplotlib.pyplot import bar, show, hist, grid, legend

def dist(x, P, N):
    X = []

    U = uniform.rvs(size = N)

    for i in range (N):
        k = 0
        sum_prob = 0

        for p in P:
            if sum_prob < U[i] < sum_prob + p:
                break
            sum_prob += p
            k += 1

        X.append(x[k])

    bin_edges = [k + 0.5 for k in range(-1, 4)]
    hist(X, bin_edges, density=True, rwidth=0.9, color='green', edgecolor='black', alpha=0.5,
         label='relative frequencies')

    distribution = dict([(x[i], P[i]) for i in range(0, len(x))])
    bar(distribution.keys(), distribution.values(), width=0.85, color='red', edgecolor='black', alpha=0.6,
        label='probabilities')

    legend(loc='lower left')
    grid()
    show()

dist([0, 1, 2, 3], [0.46, 0.4, 0.1, 0.04], 1000)