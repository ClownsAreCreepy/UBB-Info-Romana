from scipy.stats import binom
from matplotlib.pyplot import bar, hist, grid, show, legend

X = binom.rvs(5, 0.6, size=1000)

print("a) Lista de 1000 de valori = ", X)

# Probabilitatea de a obtine k succese in n incercari
# binom.pmf()


bin_edges = [k + 0.5 for k in range(6)]

hist(X, bin_edges, density=True, rwidth=0.9, color='green', edgecolor='black', alpha=0.5,
     label='relative frequencies')

distribution = dict([(i, binom.pmf(i, 5, 0.6)) for i in range(0, 6)])
bar(distribution.keys(), distribution.values(), width=0.85, color='red', edgecolor='black', alpha=0.6,
    label='probabilities')

legend(loc='lower left')
grid()
show()

print("c) Theoretical value of P(2 < X <= 5) = ", 1 - binom.cdf(2, 5, 0.6))
# Suma probabilitatilor de a obtine de la 0 la k succese
# binom.cdf(k, n, p)

count = 0
for i in X:
    if i < 3:
        count += 1
print("Estimation in X: ", 1 - count / 1000)
