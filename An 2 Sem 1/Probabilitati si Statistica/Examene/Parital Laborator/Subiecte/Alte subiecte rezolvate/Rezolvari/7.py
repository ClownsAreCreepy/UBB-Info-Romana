from matplotlib.pyplot import hist, grid, show, plot
from scipy.stats import expon
from numpy import std, mean, linspace

# a)
times = expon.rvs(scale = 4, size = 4000)
# print(times)

# b)
print(std(times))

# c)
hist(times, bins= 12, range=(0, 18), density=True, color="blue", edgecolor='k')

x = linspace(0, 18, num=4000)
plot(x, expon.pdf(x, scale=4), 'r-')

grid()
show()

# d)
fav = 0
for t in times:
    if t > 5:
        fav += 1
print("P(T > 5) =", fav / 4000, "empirically")
# sau mai simplu
# print("P(T > 5 =", mean(times > 5), "empirically")

print("P(T > 5) =", 1 - expon.cdf(5, scale=4), "theoretically")
