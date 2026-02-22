from scipy.stats import uniform
from numpy import exp, mean
from scipy.integrate import quad

n = 5000
u = uniform.rvs(loc = -1, scale = 4, size = n)
g = lambda x : exp(-x**2)
print("Aproximare:",mean(4*g(u)))
print("Valoare for real:",quad(g, -1, 3))