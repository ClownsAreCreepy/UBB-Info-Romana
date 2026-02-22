from scipy.stats import uniform, expon
from numpy import mean, std, multiply

n = 5000

# a)
r = uniform.rvs(size = n)
data = expon.rvs(loc = 0, scale = 5, size = n) * (r < 0.4) + uniform.rvs(loc=4, scale = 2, size = n) * (r >= 0.4)
print("Valoarea medie:", data.mean())
print("Deviatia standard:", std(data))

# b)
print("Probabilitatea ca timpul sa fie < 5:", mean(data < 5))

# c)
p_teorietic = 0.4 * expon.cdf(5, loc = 0, scale = 5) + 0.6 * uniform.cdf(5, loc = 4, scale = 2)
print("Probabilitatea teoretica ca timpul sa fie < 5:",p_teorietic)

